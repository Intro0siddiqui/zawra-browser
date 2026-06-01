#!/bin/bash
#
# thermal_release.sh
# Monitors CPU temperature and pauses/resumes the ninja WebKit build
# to prevent overheating. (Release build)
#

set -e

# --- Configuration ---
BUILD_DIR="webkit/build/WPE/Release"
TARGET="MiniBrowser"
JOBS=2              # i3-6006U has 4 threads; 3 jobs leaves 1 free for OS/thermal
TEMP_HIGH=63        # User preferred — conservative pause threshold
TEMP_LOW=50         # User preferred — conservative resume threshold
POLL_INTERVAL=5     # seconds between temperature checks

# Find the thermal zone
THERMAL_ZONE=""
for z in /sys/class/thermal/thermal_zone*/temp; do
    if [ -f "$z" ]; then
        # Prefer x86_pkg_temp if available (usually zone 2 or 0)
        TYPE=$(cat "$(dirname "$z")/type" 2>/dev/null || echo "")
        if [ "$TYPE" == "x86_pkg_temp" ]; then
            THERMAL_ZONE="$z"
            break
        fi
        [ -z "$THERMAL_ZONE" ] && THERMAL_ZONE="$z"
    fi
done

if [ -z "$THERMAL_ZONE" ]; then
    echo "ERROR: No thermal zone found. Cannot monitor temperature."
    exit 1
fi

get_temp() {
    local raw=$(cat "$THERMAL_ZONE")
    echo "$((raw / 1000))"
}

print_stats() {
    local temp=$1
    local state=$2
    echo -ne " \r[$(date +%H:%M:%S)] Temp: ${temp}°C | State: ${state}   "
}

echo "🚀 Starting Zawra Release Build (Thermal Burst Controller)"
echo "   Target: $TARGET | Jobs: $JOBS"
echo "   Limit: Pause >= ${TEMP_HIGH}°C | Resume <= ${TEMP_LOW}°C"
echo "   Thermal Zone: $THERMAL_ZONE ($(cat "$(dirname "$THERMAL_ZONE")/type"))"
echo ""

# Enable job control for PGID management
set -m
ninja -C "$BUILD_DIR" "$TARGET" -j "$JOBS" &
NINJA_PID=$!

# Wait for process to initialize and PGID to be available
sleep 1
NINJA_PGID=$(ps -o pgid= -p $NINJA_PID | tr -d ' ')

if [ -z "$NINJA_PGID" ]; then
    echo -e "\n❌ Failed to retrieve Build Process Group ID. Exiting."
    exit 1
fi

cleanup() {
    trap - SIGINT SIGTERM
    echo -e "\n\n🛑 Stopping build processes..."
    if [ -n "$NINJA_PGID" ]; then
        kill -TERM -"$NINJA_PGID" 2>/dev/null || true
    fi
    exit 1
}

trap cleanup SIGINT SIGTERM

STATE="RUNNING"

while true; do
    if ! kill -0 "$NINJA_PID" 2>/dev/null; then
        wait "$NINJA_PID"
        EXIT_CODE=$?
        if [ $EXIT_CODE -eq 0 ]; then
            echo -e "\n\n✅ Build finished successfully."
        else
            echo -e "\n\n❌ Build failed with exit code $EXIT_CODE."
        fi
        break
    fi

    TEMP=$(get_temp)
    
    if [ "$STATE" == "RUNNING" ]; then
        if [ "$TEMP" -ge "$TEMP_HIGH" ]; then
            kill -STOP -"$NINJA_PGID"
            STATE="PAUSED (HOT)"
        fi
    elif [ "$STATE" == "PAUSED (HOT)" ]; then
        if [ "$TEMP" -le "$TEMP_LOW" ]; then
            kill -CONT -"$NINJA_PGID"
            STATE="RUNNING"
        fi
    fi

    print_stats "$TEMP" "$STATE"
    sleep "$POLL_INTERVAL"
done

exit $EXIT_CODE
