#!/usr/bin/env bash

# Variables
# Whether to print debug messages
: "${VERBOSE:=true}"
# Whether to remove static arguments (see "Aggressive General debloating specifications")
: "${CUT_ARGS:=false}"

function file_exists {
	test -f "${1}"
}

function die {
	echo >&2 "Fatal:" "${@}"
	exit 1
}

function debug {
	if [ "${VERBOSE}" = true ]; then echo "|" "${1}"; fi
}

function which {
	command which "${1}" 2>/dev/null || echo ""
}

# https://stackoverflow.com/a/21188136
function realpath {
	# $1 : relative filename
	filename=$1
	parentdir=$(dirname "${filename}")

	if [ -d "${filename}" ]; then
		# shellcheck disable=SC2005
		echo "$(cd "${filename}" && pwd)"
	elif [ -d "${parentdir}" ]; then
		echo "$(cd "${parentdir}" && pwd)/$(basename "${filename}")"
	fi
}

function wait_kill {
	if [ "${1}" -ne 0 ]; then
		kill "${1}"
		while kill -0 "${1}" 2>/dev/null; do
			sleep 0.1
		done
	fi
}
