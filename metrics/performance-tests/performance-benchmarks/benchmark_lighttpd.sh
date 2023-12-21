#!/usr/bin/env bash

set -euo pipefail

source "lib/lighttpd.sh"

DEFAULT_BIN="${BIN}"

# ----- Input variables for benchmarking
BIN="${1:-${BIN}}"
: "${TIMES:=100}"

function usage {
	echo "usage: ${0} [<lighttpd_binary_path>]"
	echo ""
	echo "Default lighttpd path: '${DEFAULT_BIN}'"
	echo ""
	echo "Optional environment variables to set:"
	echo "                          'CLIENT': Client to execute commands for the server (${CLIENT})"
	echo "                           'TIMES': Number of times to run the scenario (${TIMES})"
	echo "          'SERVER_STATIC_ALL_CONF': Path to server configuration under test (${SERVER_STATIC_ALL_CONF})"
	echo "  'SERVER_STATIC_EXCLUDE_PHP_CONF': Path to server configuration under test (${SERVER_STATIC_EXCLUDE_PHP_CONF})"
	echo "        'SERVER_STATIC_INDEX_CONF': Path to server configuration under test (${SERVER_STATIC_INDEX_CONF})"
	echo "        'SERVER_STATIC_VHOST_CONF': Path to server configuration under test (${SERVER_STATIC_VHOST_CONF})"
	echo "                         'VERBOSE': Print progress (${VERBOSE})"
}

if [[ "${1:-}" == "-h" ]]; then
	usage
	exit 0
fi

function scenario {
	get-root_file
	get-nested_file
	get-index
	get-include_ext
	get-exclude_ext
	get-vhost_1
	get-vhost_2
	get-vhost_3
}

# Cleanup if this script dies for some reason
trap "cleanup" SIGINT SIGTERM EXIT

start_server_all

for round in $(seq "${TIMES}"); do
	debug "Round ${round}/${TIMES}"
	scenario
done

cleanup
