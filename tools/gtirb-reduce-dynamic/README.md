GTIRB Binary Reduce Dynamic uses gtirb-block-trace.

# Installing the tool

The tool can be built from the gtirb-block-trace repository on gitlab.tpcp.io,
see the `./Dockerfile` in this directory.

# Debloating with the tool

Disassemble the binary into GTIRB with ddisasm:

```
ddisasm binary --ir binary.gtirb
```

Instrument the GTIRB so that the basic blocks in the binary can be traced:

```
gtirb-block-trace --instrument binary.gtirb -o binary.instr.gtirb
```

Binary print the instrumented binary:

```
gtirb-pprinter --policy complete --ir binary.instr.gtirb --binary binary.instr
```

Generate trace data:

```
GTIRB_PROFILE_FILE=$(pwd)/trace.data binary.instr --help
```

Use the trace data to reduce the gtirb:

```
gtirb-block-trace reduce binary.gtirb --trace trace.data -o binary.reduced.gtirb
```

Binary print the gtirb:

```
gtirb-pprinter --policy complete \
  --ir binary.reduced.gtirb \
  --binary binary.reduced
```

# Debloating gzip so that it can only compress

The steps are pretty much identical to the above guide, except that we use a
small test script to exercise gzip's compression functionality, to hopefully 
cover all of it.  The test script is under the `./compression-test` directory.
It works by running the binary indicated by the `$GZIP_BIN` environment variable
on the test data in the `./compression-test/data` directory.  No compiler flags
or any features besides passing gzip a file to compress (like `gzip [file]`) 
are exercised.


```bash
# Disassemble and instrument gzip
$ ddisasm $(which gzip) --ir gzip.gtirb
$ gtirb-block-trace instrument gzip.gtirb -o gzip.instr.gtirb
$ gtirb-pprinter --policy complete --ir gzip.instr.gtirb --binary gzip.instr
# Run the test script to get trace data
$ GTIRB_PROFILE_FILE=$(pwd)/trace.data GZIP_BIN=$(pwd)/gzip.instr ./test.sh 
# Debloat and binary print gzip
$ gtirb-block-trace reduce gzip.gtirb --trace trace.data -o gzip.reduced.gtirb
$ gtirb-pprinter --policy complete --ir gzip.reduced.gtirb --binary gzip.reduced
```

The test data consists of gzip's README, the GrammaTech logo in png format, 
and trace output from gtirb-block-trace.  Trace output was successively added 
to the data directory until the reduced gzip was able to compress the trace 
output from the latest run.
