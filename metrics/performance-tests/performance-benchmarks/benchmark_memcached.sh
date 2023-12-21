#!/usr/bin/env bash

set -euo pipefail

source "lib/memcached.sh"

DEFAULT_BIN="${BIN}"

# ----- Input variables for benchmarking
BIN="${1:-${BIN}}"
: "${TIMES:=100}"

function usage {
	echo "usage: ${0} [<memcached_binary_path>]"
	echo ""
	echo "Default memcached path: '${DEFAULT_BIN}'"
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
	client_exec "$(c_set_get)
$(c_add)
$(c_add_existing)
$(c_replace)
$(c_replace_exists)
$(c_append)
$(c_append_error)
$(c_prepend)
$(c_prepend_error)
$(c_delete)
$(c_delete_error)
$(c_incr)
$(c_incr_error)
$(c_decr)
$(c_decr_error)

# Clear all data
$(c_flush)
"
}

# Cleanup if this script dies for some reason
trap "cleanup" SIGINT SIGTERM EXIT

start_server

for round in $(seq "${TIMES}"); do
	debug "Round ${round}/${TIMES}"
	scenario
done

cleanup
