#!/usr/bin/env bash

set -euo pipefail

source "lib/objdump.sh"

DEFAULT_BIN="${BIN}"

# ----- Input variables for benchmarking
BIN="${1:-${BIN}}"
: "${TIMES:=500}"

function usage {
	echo "usage: ${0} [<objdump_binary_path>]"
	echo ""
	echo "Default objdump path: '${DEFAULT_BIN}'"
	echo ""
	echo "Optional environment variables to set:"
	echo "          'TIMES': Number of times to run the scenario (${TIMES})"
	echo "   'STATIC_INPUT': Path to static input file under test (${STATIC_INPUT})"
	echo "  'DYNAMIC_INPUT': Path to dynamic input file under test (${DYNAMIC_INPUT})"
	echo "        'VERBOSE': Print progress (${VERBOSE})"
	echo "       'CUT_ARGS': Remove static CLI arguments (${CUT_ARGS})"
}

if [[ "${1:-}" == "-h" ]]; then
	usage
	exit 0
fi

function scenario {
	aggressive_static
	aggressive_dynamic
}

for round in $(seq "${TIMES}"); do
	debug "Round ${round}/${TIMES}"
	scenario
done
