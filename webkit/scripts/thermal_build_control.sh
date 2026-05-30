#!/bin/bash
#
# Zawra Browser — Thermal Build Controller (2026 Edition)
# Optimized for: High-Frequency Bursts and x86_pkg_temp.
#

set -e

# --- Configuration ---
BUILD_DIR="webkit/build/WPE/Debug"
TARGET="MiniBrowser"
JOBS=2
TEMP_HIGH=63
TEMP_LOW=45
POLL_INTERVAL=3  # Seconds between checks
THERMAL_ZONE="/sys/class/thermal/thermal_zone2/temp" # x86_pkg_temp

get_temp() {
    echo "$(( $(cat "$THERMAL_ZONE") / 1000 ))"
}

print_stats() {
    local temp=$1
    local state=$2
    echo -e " \r[$(date +%H:%M:%S)] Temp: ${temp}°C | State: ${state}   " | tr -d '\n'
}

echo "🚀 Starting Zawra Build (Thermal Burst Controller)"
echo "   Target: $TARGET | Jobs: $JOBS"
echo "   Limit: Pause >= ${TEMP_HIGH}°C | Resume <= ${TEMP_LOW}°C"
echo ""

# Enable job control for PGID management
set -m
ninja -C "$BUILD_DIR" "$TARGET" -j "$JOBS" &
NINJA_PID=$!
# Wait a moment for the process group to be established
sleep 0.5
NINJA_PGID=$(ps -o pgid= -p $NINJA_PID | tr -d ' ')

cleanup() {
    echo -e "\n\n🛑 Shutting down..."
    # Kill the entire process group
    kill -TERM -"$NINJA_PGID" 2>/dev/null || true
    exit 0
}
trap cleanup SIGINT SIGTERM EXIT

STATE="RUNNING"

while true; do
    if ! kill -0 "$NINJA_PID" 2>/dev/null; then
        echo -e "\n\n✅ Build finished or exited."
        exit 0
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
