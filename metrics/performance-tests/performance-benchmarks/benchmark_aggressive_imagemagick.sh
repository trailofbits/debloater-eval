#!/usr/bin/env bash

set -euo pipefail

source "lib/imagemagick.sh"

DEFAULT_BIN="${BIN}"

# ----- Input variables for benchmarking
BIN=${1:-${BIN}}
: "${TIMES:=100}"

function usage {
	echo "usage: ${0} [<convert_binary_path>]"
	echo ""
	echo "Default imagemagick convert path: '${DEFAULT_BIN}'"
	echo ""
	echo "Optional environment variables to set:"
	echo "     'TIMES': Number of times to run the scenario (${TIMES})"
	echo "   'JPG_IMG': Path to JPG input file under test (used in all other tests aside from conversion) (${JPG_IMG})"
	echo "   'VERBOSE': Print progress (${VERBOSE})"
	echo "  'CUT_ARGS': Remove static CLI arguments (${CUT_ARGS})"
}

if [[ "${1:-}" == "-h" ]]; then
	usage
	exit 0
fi

function scenario {
	aggressive_flip
}

for round in $(seq "${TIMES}"); do
	debug "Round ${round}/${TIMES}"
	scenario
done
