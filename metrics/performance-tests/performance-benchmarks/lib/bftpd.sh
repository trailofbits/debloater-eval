#!/usr/bin/env bash

# ----- Common functionality
SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)
# shellcheck source=lib/core.sh
source "${SCRIPT_DIR}/core.sh"

# ----- Defaults
DEFAULT_SERVER_CONF="${SCRIPT_DIR}/../inputs/bftpd/default-anon.conf"
DEFAULT_SERVER_DENY_CONF="${SCRIPT_DIR}/../inputs/bftpd/disabled-cmds-anon.conf"
DEFAULT_CLIENT_CONF="${SCRIPT_DIR}/../inputs/bftpd/lftp.rc"

# Fix server configuration for correct paths
ABS_INPUTS="$(realpath "${SCRIPT_DIR}/../inputs/bftpd")"
sed "s#{{workdir}}#${ABS_INPUTS}#g" "${DEFAULT_SERVER_CONF}.in" >"${DEFAULT_SERVER_CONF}"
sed "s#{{workdir}}#${ABS_INPUTS}#g" "${DEFAULT_SERVER_DENY_CONF}.in" >"${DEFAULT_SERVER_DENY_CONF}"

# ----- Input variables for benchmarking
: "${BIN:=$(which bftpd)}"
: "${CLIENT:=$(which lftp)}"
: "${SERVER_CONF:=${DEFAULT_SERVER_CONF}}"
: "${SERVER_DENY_CONF:=${DEFAULT_SERVER_DENY_CONF}}"
: "${CLIENT_CONF:=${DEFAULT_CLIENT_CONF}}"

# ---- Helpers
function _assert_exists {
	file_exists "${1}" || die "Could not find file '${1}'"
}

# Server process ID
SERVER_PID=0

function start_server {
	_assert_exists "${SERVER_CONF}"
	"${BIN}" -D -c "${SERVER_CONF}" &
	SERVER_PID=$!
}

function start_aggressive_server {
	_assert_exists "${SERVER_DENY_CONF}"
	if [ "${CUT_ARGS}" = true ]; then
		debug "Starting server (aggressive) (cut args)"
		pushd "$(dirname "${SERVER_DENY_CONF}")" || exit
		"${BIN}" &
		SERVER_PID=$!
		popd || exit
	else
		debug "Starting server (aggressive)"
		"${BIN}" -D -c "${SERVER_DENY_CONF}" &
		SERVER_PID=$!
	fi
}

function cleanup {
	wait_kill ${SERVER_PID}
	SERVER_PID=0
}

function c_exec {
	"${CLIENT}" --rcfile "${CLIENT_CONF}" <<<"${1}"
}

# ----- Benchmarking functions

function c_aggressive {
	c_exec "rm file.txt" || true
	c_exec "rmdir child" || true
	c_exec "chmod 440 file.txt" || true
}

# This function returns commands for the client
function c_get_file {
	echo "get file.txt"
}

# This function returns commands for the client
function c_navigate {
	commands="
    ls
    cd child
    ls
    cd ..
    ls
    "
	echo "${commands}"
}
