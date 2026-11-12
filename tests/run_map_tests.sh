#!/usr/bin/env bash
# Map validation tests for cub3D.
#  - Every map in assets/maps/bad must be rejected by the parser with
#    "Error\n" on stderr and a non-zero exit status (checked with valgrind for
#    leaks if available). A bad map that is still running after BAD_TIMEOUT
#    seconds (it was accepted and opened a window) or that only fails because
#    the window could not be opened (it was accepted by the parser) is a FAIL.
#  - Every map in assets/maps/good must start and keep running until the
#    timeout (requires an X display, e.g. run under xvfb-run).
# Requires GNU timeout (on macOS: `brew install coreutils`, which provides
# gtimeout).
# Usage: tests/run_map_tests.sh [path/to/cub3D]

set -u
BIN="${1:-./cub3D}"
TIMEOUT="${TIMEOUT:-3}"
BAD_TIMEOUT="${BAD_TIMEOUT:-30}"
fail=0
pass=0

if [ ! -x "$BIN" ]; then
	echo "binary not found: $BIN" >&2
	exit 2
fi

if command -v timeout >/dev/null 2>&1; then
	TIMEOUT_CMD=timeout
elif command -v gtimeout >/dev/null 2>&1; then
	TIMEOUT_CMD=gtimeout
else
	echo "GNU timeout not found (needed to stop wrongly accepted maps)." >&2
	echo "Install coreutils (macOS: brew install coreutils)." >&2
	exit 2
fi

VALGRIND=""
if command -v valgrind >/dev/null 2>&1 && [ -z "${NO_VALGRIND:-}" ]; then
	VALGRIND="valgrind -q --leak-check=full --errors-for-leak-kinds=definite,indirect --error-exitcode=42"
fi

report() {
	if [ "$1" = ok ]; then
		pass=$((pass + 1))
		echo "[OK]   $2"
	else
		fail=$((fail + 1))
		echo "[FAIL] $2: $3"
	fi
}

for map in assets/maps/bad/*; do
	err=$("$TIMEOUT_CMD" -k 5 "$BAD_TIMEOUT" $VALGRIND "$BIN" "$map" 2>&1 >/dev/null)
	status=$?
	reason=$(printf '%s\n' "$err" | sed -n 2p)
	if [ "$status" -eq 124 ] || [ "$status" -eq 137 ]; then
		report ng "$map" "accepted an invalid map (still running after ${BAD_TIMEOUT}s)"
	elif [ "$status" -eq 42 ]; then
		report ng "$map" "memory error/leak detected"
		echo "$err" | sed 's/^/        /'
	elif [ "$status" -eq 0 ]; then
		report ng "$map" "accepted an invalid map"
	elif [ "$(printf '%s\n' "$err" | head -n 1)" != "Error" ]; then
		report ng "$map" "stderr does not start with 'Error'"
	elif [ "$reason" = "Platform initialization failed" ]; then
		report ng "$map" "accepted an invalid map (passed the parser, failed only at window creation)"
	else
		report ok "$map ($reason)"
	fi
done

if [ -n "${DISPLAY:-}" ]; then
	for map in assets/maps/good/*.cub; do
		out=$("$TIMEOUT_CMD" "$TIMEOUT" "$BIN" "$map" 2>&1)
		status=$?
		if [ "$status" -eq 124 ]; then
			report ok "$map"
		else
			report ng "$map" "exit $status: $(echo "$out" | tr '\n' ' ')"
		fi
	done
else
	echo "DISPLAY is not set: skipping good maps (run under xvfb-run)"
fi

echo "passed: $pass, failed: $fail"
[ "$fail" -eq 0 ]
