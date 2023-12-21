#!/usr/bin/env bash

# ----- Common functionality
SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)
# shellcheck source=lib/core.sh
source "${SCRIPT_DIR}/core.sh"

# ----- Defaults
WORKDIR="${SCRIPT_DIR}/../inputs/grep"

# ----- Input variables for benchmarking
: "${BIN:=$(which grep)}"

# ---- Helpers

# ----- Benchmarking functions

function aggressive_regex {
	if [ "${CUT_ARGS}" = true ]; then
		debug "Regex (aggressive) (cut args)"
		"${BIN}" "${WORKDIR}/input_dir/input2"
	else
		debug "Regex (aggressive)"
		"${BIN}" -E free[^[:space:]]+ "${WORKDIR}/input_dir/input2"
	fi
}

function all {
	"${BIN}" a "${WORKDIR}/input_dir/input"
	"${BIN}" a -v -H -r "${WORKDIR}/input_dir"
	"${BIN}" 1 -h -r "${WORKDIR}/input_dir"
	"${BIN}" -n si "${WORKDIR}/input_dir/input2"
	"${BIN}" 1 -r "${WORKDIR}/input_dir" -l
	"${BIN}" 1 -r "${WORKDIR}/input_dir" -L
	"${BIN}" randomtext -r "${WORKDIR}/input_dir" -c
	"${BIN}" -o [r][a][n][d]* "${WORKDIR}/input_dir/input2"
	"${BIN}" 1 -r "${WORKDIR}/input_dir" -q
	"${BIN}" 1 -r "${WORKDIR}/input_dir" -s
	"${BIN}" -v a "${WORKDIR}/input_dir/input2"
	"${BIN}" -i Si "${WORKDIR}/input_dir/input2"
	"${BIN}" -w Si "${WORKDIR}/input_dir/input2"
	"${BIN}" -x Don\'t "${WORKDIR}/input_dir/input2"
	"${BIN}" -E randomtext* "${WORKDIR}/input_dir/input2"
	"${BIN}" 'ye ' "${WORKDIR}/input_dir/input"
	"${BIN}" cold "${WORKDIR}/input_dir/input"
	"${BIN}" ^D "${WORKDIR}/input_dir/input2"
	"${BIN}" .$ "${WORKDIR}/input_dir/input2"
	"${BIN}" ^ "${WORKDIR}/input_dir/input2"
	"${BIN}" ^$ "${WORKDIR}/input_dir/input2"
	"${BIN}" ^[AEIOU] "${WORKDIR}/input_dir/input2"
	"${BIN}" ^[^AEIOU] "${WORKDIR}/input_dir/input2"
	"${BIN}" -F randomtext* "${WORKDIR}/input_dir/input2"
	"${BIN}" 'not exist' "${WORKDIR}/input_dir/input"
	"${BIN}" -E free[^[:space:]]+ "${WORKDIR}/input_dir/input2"
	"${BIN}" -E "\b(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)" "${WORKDIR}/input_dir/input" || true
}
