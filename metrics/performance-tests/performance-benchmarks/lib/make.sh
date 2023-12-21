#!/usr/bin/env bash

# ----- Common functionality
SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)
# shellcheck source=lib/core.sh
source "${SCRIPT_DIR}/core.sh"

# ----- Defaults
WORKDIR="${SCRIPT_DIR}/../inputs/make"

# ----- Input variables for benchmarking
: "${BIN:=$(which make)}"

# ---- Helpers

function exec_newdir {
	tmp_dir="$(mktemp -d)"
	(
		cd "${tmp_dir}" || exit 1
		"$@"
	)
	if [ -d "${tmp_dir}" ]; then
		rm -rf "${tmp_dir}"
	fi
}

# ----- Benchmarking functions

function all {
	exec_newdir "${BIN}" -f "${WORKDIR}/high-includes.mak"
	exec_newdir "${BIN}" -f "${WORKDIR}/high-vars.mak"
}

function aggressive_install {
	args=""
	if [ "${CUT_ARGS}" = true ]; then
		debug "Install (aggressive) (cut args)"
	else
		debug "Install (aggressive)"
		args="install"
	fi

	tmp_dir="$(mktemp -d)"
	cp "${WORKDIR}/high-vars.mak" "${tmp_dir}/Makefile"
	(
		cd "${tmp_dir}" || exit 1
		"${BIN}" "${args}"
	)

	if [ -d "${tmp_dir}" ]; then
		rm -rf "${tmp_dir}"
	fi
}
