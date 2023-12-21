#!/usr/bin/env bash

set -euo pipefail

source "lib/wget.sh"

DEFAULT_BIN="${BIN}"

# ----- Input variables for benchmarking
BIN="${1:-${BIN}}"
: "${TIMES:=10}"

function usage {
	echo "usage: ${0} [<wget_binary_path>]"
	echo ""
	echo "This benchmark makes internet requests."
	echo ""
	echo "Default wget path: '${DEFAULT_BIN}'"
	echo ""
	echo "Optional environment variables to set:"
	echo "          'TIMES': Number of times to run the scenario (${TIMES})"
	echo "        'VERBOSE': Print progress (${VERBOSE})"
}

if [[ "${1:-}" == "-h" ]]; then
	usage
	exit 0
fi

function scenario {
	aggressive_protocol_https
}

for round in $(seq "${TIMES}"); do
	debug "Round ${round}/${TIMES}"
	scenario
done
