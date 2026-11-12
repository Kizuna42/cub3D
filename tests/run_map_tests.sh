#!/usr/bin/env bash
# Map validation tests for cub3D.
#  - Every map in assets/maps/bad must be rejected by the parser with
#    "Error\n" on stderr and a non-zero exit status (checked with valgrind for
#    leaks if available). A bad map that is still running after BAD_TIMEOUT
#    seconds (it was accepted and opened a window) or that only fails because
#    the window could not be opened (it was accepted by the parser) is a FAIL.
#  - Every map in assets/maps/good must start and keep running until the
#    timeout (requires an X display, e.g. run under xvfb-run).
#  - Huge maps (BIG_SIZE x BIG_SIZE, default 1000) are generated into a
#    temporary directory and tested the same way, to make sure the map
#    closure check (flood fill) does not overflow the stack.
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

BIG_SIZE="${BIG_SIZE:-1000}"
BIG_DIR=$(mktemp -d) || exit 2
trap 'rm -rf "$BIG_DIR"' EXIT

# gen_big_map <file> <size> <hole>: a size x size map fully walled, with the
# player at (1,1) and every other inner cell walkable. If <hole> is 1, the
# wall cell in the bottom-right corner area (farthest from the player) is
# replaced by a walkable cell, so the map is not closed.
gen_big_map() {
	{
		printf 'NO ./assets/textures/north_wall.xpm\n'
		printf 'SO ./assets/textures/south_wall.xpm\n'
		printf 'WE ./assets/textures/west_wall.xpm\n'
		printf 'EA ./assets/textures/east_wall.xpm\n'
		printf 'F 220,100,0\nC 225,30,0\n\n'
		awk -v n="$2" -v hole="$3" 'BEGIN {
			for (y = 0; y < n; y++) {
				row = ""
				for (x = 0; x < n; x++) {
					c = "0"
					if (x == 0 || y == 0 || x == n - 1 || y == n - 1)
						c = "1"
					if (x == 1 && y == 1)
						c = "N"
					if (hole && y == n - 1 && x == n - 2)
						c = "0"
					row = row c
				}
				print row
			}
		}'
	} > "$1"
}
gen_big_map "$BIG_DIR/bad_huge_open.cub" "$BIG_SIZE" 1
gen_big_map "$BIG_DIR/good_huge_closed.cub" "$BIG_SIZE" 0

report() {
	if [ "$1" = ok ]; then
		pass=$((pass + 1))
		echo "[OK]   $2"
	else
		fail=$((fail + 1))
		echo "[FAIL] $2: $3"
	fi
}

for map in assets/maps/bad/* "$BIG_DIR/bad_huge_open.cub"; do
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
	for map in assets/maps/good/*.cub "$BIG_DIR/good_huge_closed.cub"; do
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
