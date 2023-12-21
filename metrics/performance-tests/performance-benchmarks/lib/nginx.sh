#!/usr/bin/env bash

# ----- Common functionality
SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)
# shellcheck source=lib/core.sh
source "${SCRIPT_DIR}/core.sh"

# ----- Defaults
DEFAULT_FILE_SERVER_CONF="${SCRIPT_DIR}/../inputs/nginx/configs/file_server.conf"
DEFAULT_FILE_SERVER_VHOST_CONF="${SCRIPT_DIR}/../inputs/nginx/configs/file_server_vhost.conf"
DEFAULT_PROXY_SERVER_CONF="${SCRIPT_DIR}/../inputs/nginx/configs/proxy.conf"

DEFAULT_WORKDIR="$(realpath "${SCRIPT_DIR}/../inputs/nginx")"

# ----- Input variables for benchmarking
: "${BIN:=$(which nginx)}"
: "${CLIENT:=$(which wget)}"
: "${FILE_SERVER_CONF:=${DEFAULT_FILE_SERVER_CONF}}"
: "${FILE_SERVER_VHOST_CONF:=${DEFAULT_FILE_SERVER_VHOST_CONF}}"
: "${PROXY_SERVER_CONF:=${DEFAULT_PROXY_SERVER_CONF}}"
: "${WORKDIR:=${DEFAULT_WORKDIR}}"

# ---- Helpers
function _assert_exists {
	file_exists "${1}" || die "Could not find file '${1}'"
}

# Server process ID
FILE_SERVER_PID=0
FILE_SERVER_VHOST_PID=0
PROXY_SERVER_PID=0
PYTHON_SERVER_PID=0

function start_server_all {
	"${BIN}" -p "${WORKDIR}" -c "${FILE_SERVER_CONF}" &
	FILE_SERVER_PID=$!
	"${BIN}" -p "${WORKDIR}" -c "${FILE_SERVER_VHOST_CONF}" &
	FILE_SERVER_VHOST_PID=$!
	"${BIN}" -p "${WORKDIR}" -c "${PROXY_SERVER_CONF}" &
	PROXY_SERVER_PID=$!
	python3 -m http.server -d "${WORKDIR}/serve-ip" 8083 &>/dev/null &
	PYTHON_SERVER_PID=$!
	sleep 1
}

function cleanup {
	wait_kill ${FILE_SERVER_PID}
	FILE_SERVER_PID=0
	wait_kill ${FILE_SERVER_VHOST_PID}
	FILE_SERVER_VHOST_PID=0
	wait_kill ${PROXY_SERVER_PID}
	PROXY_SERVER_PID=0
	wait_kill ${PYTHON_SERVER_PID}
	PYTHON_SERVER_PID=0
}

function aggressive_start_server {
	if [ "${CUT_ARGS}" = true ]; then
		debug "Serving (aggressive) (cut args)"
		pushd "$(dirname "${FILE_SERVER_CONF}")" || exit
		"${BIN}" "${WORKDIR}" &
		FILE_SERVER_PID=$!
		popd || exit
	else
		debug "Serving (aggressive)"
		"${BIN}" -p "${WORKDIR}" -c "${FILE_SERVER_CONF}" &
		FILE_SERVER_PID=$!
	fi
}

function aggressive_cleanup {
	wait_kill ${FILE_SERVER_PID}
	FILE_SERVER_PID=0
}

# ----- Benchmarking functions

function file_server_download {
	"${CLIENT}" -q -O file1.html http://127.0.0.1:8080/dir1/file1.html
}

function file_server_download_relative {
	"${CLIENT}" -q -O about.html http://127.0.0.1:8080/dir1/./../about.html
}

function file_server_download_index {
	"${CLIENT}" -q -O index.html http://127.0.0.1:8080
}

function file_server_404 {
	"${CLIENT}" -q -O about.html http://127.0.0.1:8080/dir2/about.html || true
}

function file_server_vhost {
	"${CLIENT}" -q -O file1_ip.html http://127.0.0.1:8081/dir1/file1.html
	"${CLIENT}" -q -O file1_hostname.html --header "Host: vhost" http://127.0.0.1:8081/dir1/file1.html
}

function reverse_proxy {
	"${CLIENT}" -q -O file1.html http://127.0.0.1:8082/app/dir1/file1.html
}
