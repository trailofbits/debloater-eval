#!/usr/bin/env bash

# ----- Common functionality
SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)
# shellcheck source=lib/core.sh
source "${SCRIPT_DIR}/core.sh"

# ----- Defaults
DEFAULT_SERVER_STATIC_ALL_CONF="${SCRIPT_DIR}/../inputs/lighttpd/config/static-all.conf"
DEFAULT_SERVER_STATIC_EXCLUDE_PHP_CONF="${SCRIPT_DIR}/../inputs/lighttpd/config/static-exclude-php.conf"
DEFAULT_SERVER_STATIC_INDEX_CONF="${SCRIPT_DIR}/../inputs/lighttpd/config/static-index.conf"
DEFAULT_SERVER_STATIC_VHOST_CONF="${SCRIPT_DIR}/../inputs/lighttpd/config/static-vhost.conf"

# Fix server configuration for correct paths
ABS_INPUTS="$(realpath "${SCRIPT_DIR}/../inputs/lighttpd")"
sed "s#{{workdir}}#${ABS_INPUTS}#g" "${DEFAULT_SERVER_STATIC_ALL_CONF}.in" >"${DEFAULT_SERVER_STATIC_ALL_CONF}"
sed "s#{{workdir}}#${ABS_INPUTS}#g" "${DEFAULT_SERVER_STATIC_EXCLUDE_PHP_CONF}.in" >"${DEFAULT_SERVER_STATIC_EXCLUDE_PHP_CONF}"
sed "s#{{workdir}}#${ABS_INPUTS}#g" "${DEFAULT_SERVER_STATIC_INDEX_CONF}.in" >"${DEFAULT_SERVER_STATIC_INDEX_CONF}"
sed "s#{{workdir}}#${ABS_INPUTS}#g" "${DEFAULT_SERVER_STATIC_VHOST_CONF}.in" >"${DEFAULT_SERVER_STATIC_VHOST_CONF}"

# ----- Input variables for benchmarking
: "${BIN:=$(which lighttpd)}"
: "${CLIENT:=$(which wget)}"
: "${SERVER_STATIC_ALL_CONF:=${DEFAULT_SERVER_STATIC_ALL_CONF}}"
: "${SERVER_STATIC_EXCLUDE_PHP_CONF:=${DEFAULT_SERVER_STATIC_EXCLUDE_PHP_CONF}}"
: "${SERVER_STATIC_INDEX_CONF:=${DEFAULT_SERVER_STATIC_INDEX_CONF}}"
: "${SERVER_STATIC_VHOST_CONF:=${DEFAULT_SERVER_STATIC_VHOST_CONF}}"

# ---- Helpers

# Server process ID
SERVER_ALL_PID=0
SERVER_EXCLUDE_PID=0
SERVER_INDEX_PID=0
SERVER_VHOST_PID=0

function start_server_all {
	"${BIN}" -D -f "${SERVER_STATIC_ALL_CONF}" &
	SERVER_ALL_PID=$!
	"${BIN}" -D -f "${SERVER_STATIC_EXCLUDE_PHP_CONF}" &
	SERVER_EXCLUDE_PID=$!
	"${BIN}" -D -f "${SERVER_STATIC_INDEX_CONF}" &
	SERVER_INDEX_PID=$!
	"${BIN}" -D -f "${SERVER_STATIC_VHOST_CONF}" &
	SERVER_VHOST_PID=$!
	sleep 1
}

function cleanup {
	wait_kill ${SERVER_ALL_PID}
	SERVER_ALL_PID=0
	wait_kill ${SERVER_EXCLUDE_PID}
	SERVER_EXCLUDE_PID=0
	wait_kill ${SERVER_INDEX_PID}
	SERVER_INDEX_PID=0
	wait_kill ${SERVER_VHOST_PID}
	SERVER_VHOST_PID=0
}

function start_aggressive_server {
	if [ "${CUT_ARGS}" = true ]; then
		debug "Starting server (aggressive) (cut args)"
		pushd "$(dirname "${SERVER_STATIC_ALL_CONF}")" || exit
		"${BIN}" &
		SERVER_ALL_PID=$!
		popd || exit
	else
		debug "Starting server (aggressive)"
		"${BIN}" -D -f "${SERVER_STATIC_ALL_CONF}" &
		SERVER_ALL_PID=$!
	fi
}

function cleanup_aggressive_server {
	wait_kill ${SERVER_ALL_PID}
	SERVER_ALL_PID=0
}

# ----- Benchmarking functions

# This function returns commands for the client
function get-root_file {
	debug "Get-root_file"
	"${CLIENT}" -q -O index.html http://localhost:3000/index.html
}

function get-nested_file {
	debug "Get-nested_file"
	"${CLIENT}" -q -O file1.html http://localhost:3000/dir1/file1.html
}

function get-index {
	debug "Get-index"
	"${CLIENT}" -q -O index.html http://localhost:3002
}

function get-include_ext {
	debug "Get-include_ext"
	"${CLIENT}" -q -O index.html http://localhost:3001/index.html
}

function get-exclude_ext {
	debug "Get-exclude_ext"
	"${CLIENT}" -q -O run.php http://localhost:3001/run.php || true
}

function get-vhost_1 {
	debug "Get-vhost_1"
	"${CLIENT}" -q -O index.html http://127.0.0.1:3003/index.html
}

function get-vhost_2 {
	debug "Get-vhost_2"
	"${CLIENT}" -q -O hello.txt http://127.0.0.1:3003/hello.txt || true
}

function get-vhost_3 {
	debug "Get-vhost_3"
	"${CLIENT}" -q -O hello.txt http://127.0.1.1:3003/hello.txt
}
