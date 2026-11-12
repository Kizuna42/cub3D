#!/usr/bin/env bash
# Map validation tests for cub3D.
#  - Every map in assets/maps/bad must be rejected with "Error\n" on stderr
#    and a non-zero exit status (checked with valgrind for leaks if available).
#  - Every map in assets/maps/good must start and keep running until the
#    timeout (requires an X display, e.g. run under xvfb-run).
# Usage: tests/run_map_tests.sh [path/to/cub3D]

set -u
BIN="${1:-./cub3D}"
TIMEOUT="${TIMEOUT:-3}"
fail=0
pass=0

if [ ! -x "$BIN" ]; then
	echo "binary not found: $BIN" >&2
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
	err=$($VALGRIND "$BIN" "$map" 2>&1 >/dev/null)
	status=$?
	if [ "$status" -eq 42 ]; then
		report ng "$map" "memory error/leak detected"
		echo "$err" | sed 's/^/        /'
	elif [ "$status" -eq 0 ]; then
		report ng "$map" "accepted an invalid map"
	elif [ "$(printf '%s\n' "$err" | head -n 1)" != "Error" ]; then
		report ng "$map" "stderr does not start with 'Error'"
	else
		report ok "$map ($(printf '%s\n' "$err" | sed -n 2p))"
	fi
done

if [ -n "${DISPLAY:-}" ]; then
	for map in assets/maps/good/*.cub; do
		out=$(timeout "$TIMEOUT" "$BIN" "$map" 2>&1)
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
