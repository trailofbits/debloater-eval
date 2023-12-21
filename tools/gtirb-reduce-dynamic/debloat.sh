#!/bin/bash

set -e
set -x

{
  # Should be like ./bzip2
  binary=$1
  # Should be like low/bzip2
  benchmark=$2

  cp /host/benchmarks/$benchmark*/binaries/64/* ./
  cp -r /host/tool-debloating-specs/$(dirname $benchmark)/input_files /input_files

  gtirb=$1.gtirb
  instr_gtirb=$1.instr.gtirb
  instr=$1.instr
  reduced_gtirb=$1.reduced.gtirb
  reduced=$1.reduced

  /usr/bin/time -q -f %e,%S,%U,%M,%t,%K,%x ddisasm $binary --ir $gtirb
  /usr/bin/time -q -f %e,%S,%U,%M,%t,%K,%x gtirb-block-trace instrument $gtirb -o $instr_gtirb
  LD_LIBRARY_PATH="/usr/lib/x86_64-linux-gnu/:$LD_LIBRARY_PATH" /usr/bin/time -q -f %e,%S,%U,%M,%t,%K,%x gtirb-pprinter --ir $instr_gtirb --binary $instr --policy complete -L/usr/lib/x86_64-linux-gnu/ -L$(pwd)
  export CC=clang CXX=clang++

  # Razor wants to use binaries called *.orig, and the test scripts
  # emplace the name of such binaries into the chisel oracles as the "original",
  # while it will emplace the name of the binary we give it as the "reduced" binary.
  # Chisel wants to compare reduced binaries with originals, and some of the
  # binaries output their filenames, so we need to make sure that we have the same
  # binary name for both the "original" and "reduced" binaries.
  orig=$binary.orig
  cp $instr $orig
  export LD_LIBRARY_PATH=$(pwd):$LD_LIBRARY_PATH
  GTIRB_PROFILE_FILE=$(pwd)/gtirb-profile.data PYTHONPATH=/host/tool-debloating-specs/ /usr/bin/time -q -f %e,%S,%U,%M,%t,%K,%x python /host/tool-debloating-specs/gtirb_dyn_run_spec.py $benchmark $orig
  /usr/bin/time -q -f %e,%S,%U,%M,%t,%K,%x gtirb-block-trace reduce --trace $(pwd)/gtirb-profile.data -o $reduced_gtirb $gtirb
  /usr/bin/time -q -f %e,%S,%U,%M,%t,%K,%x gtirb-pprinter --ir $reduced_gtirb --binary $reduced -L/usr/lib/x86_64-linux-gnu/ -L$(pwd)

  mkdir -p /host/benchmarks-debloated/$benchmark/gtirb-dynamic
  cp *.reduced /host/benchmarks-debloated/$benchmark/gtirb-dynamic
} 2>&1 | tee debloat-log

grep -Er '.*,.*,.*,.*,.*,.*' debloat-log
