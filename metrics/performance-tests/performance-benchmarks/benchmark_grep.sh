#!/usr/bin/env bash

set -euo pipefail

source "lib/grep.sh"

DEFAULT_BIN="${BIN}"

# ----- Input variables for benchmarking
BIN=${1:-${BIN}}
: "${TIMES:=100}"

function usage {
	echo "usage: ${0} [<grep_binary_path>]"
	echo ""
	echo "Default grep path: '${DEFAULT_BIN}'"
	echo ""
	echo "Optional environment variables to set:"
	echo "    'TIMES': Number of times to run the scenario (${TIMES})"
	echo "  'VERBOSE': Print progress (${VERBOSE})"
}

if [[ "${1:-}" == "-h" ]]; then
	usage
	exit 0
fi

function scenario {
	all
}

for round in $(seq "${TIMES}"); do
	debug "Round ${round}/${TIMES}"
	scenario
done
