Chisel is a source debloater that uses an oracle to guide a
delta-debugging-based reduction.

## Usage

1) Build the docker image, which will give you a `debian:buster` environment
   with a working chisel.
1) Chisel works with a single source file, so you need to merge your
   benchmark's source into a single file.
1) Under the `/chiselbench/benchmark` directory in the docker image, create a
new directory for your benchmark, and copy your merged source file and a copy of
the `/chiselbench/benchmark/test-template.sh` oracle file into the new
directory.
1) Fill out the following information at the top of the oracle file (replace 
the TODOs)

```
BENCHMARK_NAME=[the directory name of your benchmark.  Your source file needs 
to be $BENCHMARK_NAME.c]
...
TIMEOUT=[a timeout value for the tests]
```

1) Fill out the `clean` function to clean up after the tests and to also remove
`$REDUCED_BIN`.
1) Fill out the `desired` function with the tests for desired functionality.
1) Fill out the `desired_disaster` function in a way that handles both `memory`
and `file` environments (see `/chiselbench/benchmark/test-base.sh`.
Essentially, your program will be built and tested with two different shims:
  1) One replaces memory allocation functions (`malloc` et al.) with functions
  that indicate memory allocation failed, and your job is to write tests to make
  sure that the appropriate error handling has been retained in the program, by
  checking for error messages in the output, for example.
  1) The other replaces file handle manipulation functions (`open` et al.) with
  functions that always indicate failure, and your job is to make sure that the
  appropriate error handling has been retained in the program.
1) Copy `Makefile` from one of the other benchmarks and rename the `NAME` 
variable to be the same as `BENCHMARK_NAME` from the oracle.
