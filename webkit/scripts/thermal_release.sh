#!/bin/bash
#
# Zawra Browser — Thermal Build Controller (Release Edition)
# Optimized for: High-Frequency Bursts and x86_pkg_temp.
#

set -e

# --- Configuration ---
BUILD_DIR="webkit/build/WPE/Release"
TARGET="MiniBrowser"
JOBS=2
TEMP_HIGH=63
TEMP_LOW=45
POLL_INTERVAL=3  # Seconds between checks
THERMAL_ZONE="/sys/class/thermal/thermal_zone2/temp" # x86_pkg_temp

get_temp() {
    if [ -f "$THERMAL_ZONE" ]; then
        echo "$(( $(cat "$THERMAL_ZONE") / 1000 ))"
    else
        echo "0"
    fi
}

print_stats() {
    local temp=$1
    local state=$2
    echo -ne " \r[$(date +%H:%M:%S)] Temp: ${temp}°C | State: ${state}   "
}

echo "🚀 Starting Zawra Release Build (Thermal Burst Controller)"
echo "   Target: $TARGET | Jobs: $JOBS"
echo "   Limit: Pause >= ${TEMP_HIGH}°C | Resume <= ${TEMP_LOW}°C"
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
        # Kill the entire process group
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
