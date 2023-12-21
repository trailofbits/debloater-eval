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
	echo "    'TIMES': Number of times to run the scenario (${TIMES})"
	echo "   'OUTPUT': Path to input file under test (${OUTPUT})"
	echo "   'INPUT1': Path to input file under test (${INPUT1})"
	echo "   'INPUT2': Path to input file under test (${INPUT2})"
	echo "  'VERBOSE': Print progress (${VERBOSE})"
}

if [[ "${1:-}" == "-h" ]]; then
	usage
	exit 0
fi

function scenario {
	collect
	expand
	zip
	cleanup
}

for round in $(seq "${TIMES}"); do
	debug "Round ${round}/${TIMES}"
	scenario
done
