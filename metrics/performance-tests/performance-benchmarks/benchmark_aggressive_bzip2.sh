#!/usr/bin/env bash

set -euo pipefail

source "lib/bzip2.sh"

DEFAULT_BIN="${BIN}"

# ----- Input variables for benchmarking
BIN=${1:-${BIN}}
: "${TIMES:=10}"

function usage {
	echo "usage: ${0} [<bzip2_binary_path>]"
	echo ""
	echo "Default bzip2 path: '${DEFAULT_BIN}'"
	echo ""
	echo "Optional environment variables to set:"
	echo "     'TIMES': Number of times to run the scenario (${TIMES})"
	echo "     'INPUT': Path to input file under test (${INPUT})"
	echo "   'VERBOSE': Print progress (${VERBOSE})"
	echo "  'CUT_ARGS': Remove static CLI arguments (${CUT_ARGS})"
}

if [[ "${1:-}" == "-h" ]]; then
	usage
	exit 0
fi

function scenario {
	aggressive_compress
}

for round in $(seq "${TIMES}"); do
	debug "Round ${round}/${TIMES}"
	scenario
done
