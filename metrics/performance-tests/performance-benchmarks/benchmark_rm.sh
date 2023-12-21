#!/usr/bin/env bash

set -euo pipefail

source "lib/rm.sh"

DEFAULT_BIN="${BIN}"

# ----- Input variables for benchmarking
BIN=${1:-${BIN}}
: "${TIMES:=50}"

function usage {
	echo "usage: ${0} [<rm_binary_path>]"
	echo ""
	echo "This test creates and deletes a temporary directory with other directories."
	echo ""
	echo "Default rm path: '${DEFAULT_BIN}'"
	echo ""
	echo "Optional environment variables to set:"
	echo "     'TIMES': Number of times to run the scenario (${TIMES})"
	echo "  'ROOT_DIR': Root directory to use as working dir (${ROOT_DIR})"
	echo "   'VERBOSE': Print progress (${VERBOSE})"
}

if [[ "${1:-}" == "-h" ]]; then
	usage
	exit 0
fi

function scenario {
	create
	all
}

for round in $(seq "${TIMES}"); do
	debug "Round ${round}/${TIMES}"
	scenario
done
