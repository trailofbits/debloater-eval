#!/usr/bin/env bash

set -euo pipefail

source "lib/gzip.sh"

DEFAULT_BIN="${BIN}"

# ----- Input variables for benchmarking
BIN=${1:-${BIN}}
: "${TIMES:=500}"

function usage {
	echo "usage: ${0} [<gzip_binary_path>]"
	echo ""
	echo "Default gzip path: '${DEFAULT_BIN}'"
	echo ""
	echo "Optional environment variables to set:"
	echo "             'TIMES': Number of times to run the scenario (${TIMES})"
	echo "    'COMPRESS_INPUT': Path to input file for compression under test (${COMPRESS_INPUT})"
	echo "           'VERBOSE': Print progress (${VERBOSE})"
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
