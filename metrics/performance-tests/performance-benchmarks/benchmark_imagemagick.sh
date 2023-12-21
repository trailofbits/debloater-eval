#!/usr/bin/env bash

set -euo pipefail

source "lib/imagemagick.sh"

DEFAULT_BIN="${BIN}"

# ----- Input variables for benchmarking
BIN=${1:-${BIN}}
: "${TIMES:=10}"

function usage {
	echo "usage: ${0} [<convert_binary_path>]"
	echo ""
	echo "Default imagemagick convert path: '${DEFAULT_BIN}'"
	echo ""
	echo "Optional environment variables to set:"
	echo "    'TIMES': Number of times to run the scenario (${TIMES})"
	echo "  'BMP_IMG': Path to BMP input file under test (${BMP_IMG})"
	echo "  'GIF_IMG': Path to GIF input file under test (${GIF_IMG})"
	echo "  'JPG_IMG': Path to JPG input file under test (used in all other tests aside from conversion) (${JPG_IMG})"
	echo "  'PNG_IMG': Path to PNG input file under test (${PNG_IMG})"
	echo "  'VERBOSE': Print progress (${VERBOSE})"
}

if [[ "${1:-}" == "-h" ]]; then
	usage
	exit 0
fi

function scenario {
	convert-format
	resize
	flip
	flop
	negate
	scale
	roll
	transverse
	transpose
	rotate
	crop
}

for round in $(seq "${TIMES}"); do
	debug "Round ${round}/${TIMES}"
	scenario
done
