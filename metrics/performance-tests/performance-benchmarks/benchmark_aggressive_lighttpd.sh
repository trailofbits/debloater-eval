#!/usr/bin/env bash

set -euo pipefail

source "lib/lighttpd.sh"

DEFAULT_BIN="${BIN}"

# ----- Input variables for benchmarking
BIN="${1:-${BIN}}"
: "${TIMES:=200}"

function usage {
	echo "usage: ${0} [<lighttpd_binary_path>]"
	echo ""
	echo "Default lighttpd path: '${DEFAULT_BIN}'"
	echo ""
	echo "Optional environment variables to set:"
	echo "                  'CLIENT': Client to execute commands for the server (${CLIENT})"
	echo "                   'TIMES': Number of times to run the scenario (${TIMES})"
	echo "  'SERVER_STATIC_ALL_CONF': Path to server configuration under test (${SERVER_STATIC_ALL_CONF})"
	echo "                 'VERBOSE': Print progress (${VERBOSE})"
	echo "                'CUT_ARGS': Remove static CLI arguments (${CUT_ARGS})"
}

if [[ "${1:-}" == "-h" ]]; then
	usage
	exit 0
fi

function scenario {
	get-root_file
	get-nested_file
}

# Cleanup if this script dies for some reason
trap "cleanup_aggressive_server" SIGINT SIGTERM EXIT

start_aggressive_server

for round in $(seq "${TIMES}"); do
	debug "Round ${round}/${TIMES}"
	scenario
done

cleanup_aggressive_server
