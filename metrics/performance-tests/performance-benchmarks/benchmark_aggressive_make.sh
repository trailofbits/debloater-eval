#!/usr/bin/env bash

set -euo pipefail

source "lib/make.sh"

DEFAULT_BIN="${BIN}"

# ----- Input variables for benchmarking
BIN=${1:-${BIN}}
: "${TIMES:=200}"

function usage {
	echo "usage: ${0} [<make_binary_path>]"
	echo ""
	echo "This test creates and deletes a temporary directory with files."
	echo ""
	echo "Default make path: '${DEFAULT_BIN}'"
	echo ""
	echo "Optional environment variables to set:"
	echo "     'TIMES': Number of times to run the scenario (${TIMES})"
	echo "   'VERBOSE': Print progress (${VERBOSE})"
	echo "  'CUT_ARGS': Remove static CLI arguments (${CUT_ARGS})"
}

if [[ "${1:-}" == "-h" ]]; then
	usage
	exit 0
fi

function scenario {
	aggressive_install
}

for round in $(seq "${TIMES}"); do
	debug "Round ${round}/${TIMES}"
	scenario
done
