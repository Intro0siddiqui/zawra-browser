#!/bin/bash
#
# thermal_build_control.sh
# Monitors CPU temperature and pauses/resumes the ninja WebKit build
# to prevent overheating.
#
# Usage:
#   ./thermal_build_control.sh
#
# The script starts the ninja build, monitors temperature,
# sends SIGSTOP when temp >= 63°C, and SIGCONT when temp <= 45°C.

set -e

BUILD_DIR="WebKitBuild/WPE/Debug"
TARGET="MiniBrowser"
JOBS=2
TEMP_HIGH=63
TEMP_LOW=45
POLL_INTERVAL=5  # seconds between temperature checks

# Find the thermal zone (usually thermal_zone0 on modern systems)
THERMAL_ZONE=""
for z in /sys/class/thermal/thermal_zone*/temp; do
    if [ -f "$z" ]; then
        THERMAL_ZONE="$z"
        break
    fi
done

if [ -z "$THERMAL_ZONE" ]; then
    echo "ERROR: No thermal zone found. Cannot monitor temperature."
    exit 1
fi

get_temp() {
    local raw=$(cat "$THERMAL_ZONE")
    # Temperature is in millidegrees Celsius (e.g. 55000 = 55.0°C)
    echo "$((raw / 1000))"
}

echo "Starting ninja build with thermal control..."
echo "  Pause temp: >= ${TEMP_HIGH}°C"
echo "  Resume temp: <= ${TEMP_LOW}°C"
echo "  Poll interval: ${POLL_INTERVAL}s"
echo "  Thermal zone: $THERMAL_ZONE"
echo ""

# Start the ninja build in the background
ninja -C "$BUILD_DIR" "$TARGET" -j "$JOBS" &
NINJA_PID=$!

# Trap to clean up on exit
cleanup() {
    echo ""
    echo "Shutting down..."
    kill "$NINJA_PID" 2>/dev/null || true
    wait "$NINJA_PID" 2>/dev/null || true
    exit 0
}
trap cleanup SIGINT SIGTERM EXIT

STATE="running"

while true; do
    # Check if ninja is still running
    if ! kill -0 "$NINJA_PID" 2>/dev/null; then
        echo "Build finished or exited."
        exit 0
    fi

    TEMP=$(get_temp)
    NOW=$(date +%H:%M:%S)

    case "$STATE" in
        running)
            if [ "$TEMP" -ge "$TEMP_HIGH" ]; then
                echo "[$NOW] Temp ${TEMP}°C >= ${TEMP_HIGH}°C — PAUSING build (SIGSTOP)"
                kill -SIGSTOP "$NINJA_PID"
                # Also stop any child compiler processes
                pkill -SIGSTOP -P "$NINJA_PID" 2>/dev/null || true
                STATE="paused"
            fi
            ;;
        paused)
            if [ "$TEMP" -le "$TEMP_LOW" ]; then
                echo "[$NOW] Temp ${TEMP}°C <= ${TEMP_LOW}°C — RESUMING build (SIGCONT)"
                kill -SIGCONT "$NINJA_PID"
                pkill -SIGCONT -P "$NINJA_PID" 2>/dev/null || true
                STATE="running"
            fi
            ;;
    esac

    sleep "$POLL_INTERVAL"
done
