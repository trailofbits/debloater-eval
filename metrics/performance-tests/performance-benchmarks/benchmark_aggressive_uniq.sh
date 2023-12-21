#!/usr/bin/env bash

set -euo pipefail

source "lib/uniq.sh"

DEFAULT_BIN="${BIN}"

# ----- Input variables for benchmarking
BIN=${1:-${BIN}}
: "${TIMES:=300}"

function usage {
	echo "usage: ${0} [<uniq_binary_path>]"
	echo ""
	echo "Default uniq path: '${DEFAULT_BIN}'"
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
	aggressive_ignore_case
}

for round in $(seq "${TIMES}"); do
	debug "Round ${round}/${TIMES}"
	scenario
done
