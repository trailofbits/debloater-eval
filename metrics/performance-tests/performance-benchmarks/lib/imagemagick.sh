#!/usr/bin/env bash

# ----- Common functionality
SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)
# shellcheck source=lib/core.sh
source "${SCRIPT_DIR}/core.sh"

# ----- Defaults
DEFAULT_BMP_IMG="${SCRIPT_DIR}/../inputs/imagemagick/eggs.bmp"
DEFAULT_GIF_IMG="${SCRIPT_DIR}/../inputs/imagemagick/eggs.gif"
DEFAULT_JPG_IMG="${SCRIPT_DIR}/../inputs/imagemagick/eggs.jpg"
DEFAULT_PNG_IMG="${SCRIPT_DIR}/../inputs/imagemagick/eggs.png"

# ----- Input variables for benchmarking
: "${BIN:=$(which convert)}"
: "${BMP_IMG:=${DEFAULT_BMP_IMG}}"
: "${GIF_IMG:=${DEFAULT_GIF_IMG}}"
: "${JPG_IMG:=${DEFAULT_JPG_IMG}}"
: "${PNG_IMG:=${DEFAULT_PNG_IMG}}"

# ---- Helpers
function _assert_exists {
	file_exists "${1}" || die "Could not find file '${1}'"
}

# ----- Benchmarking functions

function aggressive_flip {
	if [ "${CUT_ARGS}" = true ]; then
		debug "Flip (aggressive) (cut args)"
		"${BIN}" "${JPG_IMG}" "${JPG_IMG}-flipped.jpg"
	else
		debug "Flip (aggressive)"
		"${BIN}" "${JPG_IMG}" -flip "${JPG_IMG}-flipped.jpg"
	fi
}

function convert-format {
	debug "Converting"

	"${BIN}" "${BMP_IMG}" "${BMP_IMG}.gif"
	"${BIN}" "${BMP_IMG}" "${BMP_IMG}.jpg"
	"${BIN}" "${BMP_IMG}" "${BMP_IMG}.png"

	"${BIN}" "${GIF_IMG}" "${GIF_IMG}.bmp"
	"${BIN}" "${GIF_IMG}" "${GIF_IMG}.jpg"
	"${BIN}" "${GIF_IMG}" "${GIF_IMG}.png"

	"${BIN}" "${JPG_IMG}" "${JPG_IMG}.bmp"
	"${BIN}" "${JPG_IMG}" "${JPG_IMG}.gif"
	"${BIN}" "${JPG_IMG}" "${JPG_IMG}.png"

	"${BIN}" "${PNG_IMG}" "${PNG_IMG}.bmp"
	"${BIN}" "${PNG_IMG}" "${PNG_IMG}.gif"
	"${BIN}" "${PNG_IMG}" "${PNG_IMG}.jpg"
}

function resize {
	debug "Resizing"
	"${BIN}" "${JPG_IMG}" -resize "50%" "${JPG_IMG}-resized50.jpg"
	"${BIN}" "${JPG_IMG}" -resize "150%" "${JPG_IMG}-resized150.jpg"
}

function flip {
	debug "Flip"
	"${BIN}" "${JPG_IMG}" -flip "${JPG_IMG}-flipped.jpg"
}

function flop {
	debug "Flop"
	"${BIN}" "${JPG_IMG}" -flop "${JPG_IMG}-flopped.jpg"
}

function negate {
	debug "Negate"
	"${BIN}" "${JPG_IMG}" -negate "${JPG_IMG}-negate.jpg"
	"${BIN}" "${JPG_IMG}" +negate "${JPG_IMG}+negate.jpg"
}

function scale {
	debug "Scale"
	"${BIN}" "${JPG_IMG}" -scale "50%" "${JPG_IMG}-scaled50.jpg"
	"${BIN}" "${JPG_IMG}" -scale "150%" "${JPG_IMG}-scaled150.jpg"
}

function roll {
	debug "Roll"
	"${BIN}" "${JPG_IMG}" -roll "+0-270" "${JPG_IMG}-roll+0-270.jpg"
	"${BIN}" "${JPG_IMG}" -roll "-270-270" "${JPG_IMG}-roll-270-270.jpg"
	"${BIN}" "${JPG_IMG}" -roll "-270+0" "${JPG_IMG}-roll-270+0.jpg"
	"${BIN}" "${JPG_IMG}" -roll "+270+0" "${JPG_IMG}-roll+270+0.jpg"
	"${BIN}" "${JPG_IMG}" -roll "+270+270" "${JPG_IMG}-roll+270+270.jpg"
}

function transverse {
	debug "Transverse"
	"${BIN}" "${JPG_IMG}" -transverse "${JPG_IMG}-transverse.jpg"
}

function transpose {
	debug "Transpose"
	"${BIN}" "${JPG_IMG}" -transpose "${JPG_IMG}-transpose.jpg"
}

function rotate {
	debug "Rotate"
	"${BIN}" "${JPG_IMG}" -rotate 0 "${JPG_IMG}-rotate0.jpg"
	"${BIN}" "${JPG_IMG}" -rotate -270 "${JPG_IMG}-rotate-270.jpg"
	"${BIN}" "${JPG_IMG}" -rotate -90 "${JPG_IMG}-rotate-90.jpg"
	"${BIN}" "${JPG_IMG}" -rotate 90 "${JPG_IMG}-rotate90.jpg"
	"${BIN}" "${JPG_IMG}" -rotate 270 "${JPG_IMG}-rotate270.jpg"
	"${BIN}" "${JPG_IMG}" -rotate 360 "${JPG_IMG}-rotate360.jpg"
}

function crop {
	debug "Crop"
	"${BIN}" "${JPG_IMG}" -crop "123x100+0+90" "${JPG_IMG}-rotate123x100+0+90.jpg"
	"${BIN}" "${JPG_IMG}" -crop "100x123+90+90" "${JPG_IMG}-rotate100x123+90+90.jpg"
	"${BIN}" "${JPG_IMG}" -crop "234x123+90+0" "${JPG_IMG}-rotate234x123+90+0.jpg"
	"${BIN}" "${JPG_IMG}" -crop "50x234+0+0" "${JPG_IMG}-rotate50x234+0+0.jpg"
}
