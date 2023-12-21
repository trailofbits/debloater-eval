#!/usr/bin/env bash

set -euo pipefail

source "lib/tar.sh"

DEFAULT_BIN="${BIN}"

# ----- Input variables for benchmarking
BIN=${1:-${BIN}}
: "${TIMES:=10}"

function usage {
	echo "usage: ${0} [<tar_binary_path>]"
	echo ""
	echo "Default tar path: '${DEFAULT_BIN}'"
	echo ""
	echo "Optional environment variables to set:"
	echo "         'TIMES': Number of times to run the scenario (${TIMES})"
	echo "  'EXPAND_INPUT': Path to input file under test (${EXPAND_INPUT})"
	echo "       'VERBOSE': Print progress (${VERBOSE})"
	echo "      'CUT_ARGS': Remove static CLI arguments (${CUT_ARGS})"
}

if [[ "${1:-}" == "-h" ]]; then
	usage
	exit 0
fi

function scenario {
	aggressive_expand
}

for round in $(seq "${TIMES}"); do
	debug "Round ${round}/${TIMES}"
	scenario
done
