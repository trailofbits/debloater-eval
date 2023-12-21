#!/usr/bin/env bash

set -euo pipefail

source "lib/nginx.sh"

DEFAULT_BIN="${BIN}"

# ----- Input variables for benchmarking
BIN="${1:-${BIN}}"
: "${TIMES:=50}"

function usage {
	echo "usage: ${0} [<nginx_binary_path>]"
	echo ""
	echo "Default nginx path: '${DEFAULT_BIN}'"
	echo ""
	echo "Optional environment variables to set:"
	echo "                  'CLIENT': Client to execute commands for the server (${CLIENT})"
	echo "                   'TIMES': Number of times to run the scenario (${TIMES})"
	echo "                 'WORKDIR': Working directory to find server directories (${WORKDIR})"
	echo "        'FILE_SERVER_CONF': Path to file server configuration under test (${FILE_SERVER_CONF})"
	echo "  'FILE_SERVER_VHOST_CONF': Path to file server vhost configuration under test (${FILE_SERVER_VHOST_CONF})"
	echo "       'PROXY_SERVER_CONF': Path to proxy server configuration under test (${PROXY_SERVER_CONF})"
	echo "                 'VERBOSE': Print progress (${VERBOSE})"
}

if [[ "${1:-}" == "-h" ]]; then
	usage
	exit 0
fi

function scenario {
	file_server_download
	file_server_download_relative
	file_server_download_index
	file_server_404
	file_server_vhost
	reverse_proxy
}

# Cleanup if this script dies for some reason
trap "cleanup" SIGINT SIGTERM EXIT

start_server_all

for round in $(seq "${TIMES}"); do
	debug "Round ${round}/${TIMES}"
	scenario
done

cleanup
