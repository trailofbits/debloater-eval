#!/usr/bin/env bash

# ----- Common functionality
SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)
# shellcheck source=lib/core.sh
source "${SCRIPT_DIR}/core.sh"

# ----- Defaults
JSONTEST_IP=$(getent ahosts echo.jsontest.com | head -n 1 | awk '{ print $1 }')

# ----- Input variables for benchmarking
: "${BIN:=$(which wget)}"

# ---- Helpers

# ----- Benchmarking functions

function aggressive_protocol_https {
	"${BIN}" https://digg.com/robots.txt
}

function protocol_https {
	"${BIN}" -O robots.txt https://digg.com/robots.txt
}

function protocol_http {
	"${BIN}" -O value http://echo.jsontest.com/key/value
}

function protocol_ip {
	"${BIN}" -O value --header 'Host: echo.jsontest.com' "http://${JSONTEST_IP}/key/value"
}

function opts_timeout_ok {
	"${BIN}" -T 1 http://echoss.jsontest.com/ || true
}

function get_param {
	"${BIN}" -O data.json http://md5.jsontest.com/?text=hello_world
}
