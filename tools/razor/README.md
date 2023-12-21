Razor uses dynamorio to instrument a binary and trim out instructions that
aren't executed by a test suite.

# How to use razor

1. Get the docker image: `docker pull chenxiong/razor:0.01`
1. In the docker image, create the directory `./benchmarks/debloat-eval`
1. In the directory created in the last step, download your benchmark into its
   own directory. i.e. `./benchmarks/debloat-eval/gzip-1.12`
1. Build your benchmark and rename the resulting binary to be `[binary].orig`
1. Copy the `run_razor.py` script used by the gzip demo from the host into your benchmark's
   directory in the container:
   `docker cp run_razor.gzip-1.12.py [container]:/root/workspace/razor/benchmarks/debloat-eval/[benchmark]`
1. Modify `run_razor.py` to work with your specific benchmark:
   1. Replace the value of `binary` with your benchmark's binary
   1. In the `train` function, call train_run a number of times with each of
      your tests
1. Run `python run_razor.py train`.  This will populated a `logs` directory
   with trace information.
1. Run `python run_razor.py debloat`.  The debloated binary is located at
   `[binary].orig_temp/[binary].orig.debloated`.

# Gzip demo

Pull the image and start a container.  We mount this directory into the
container so we can access the `run_razor.py` that was created for the demo.
The remaining instructions are run in the container.

```sh
docker pull chenxiong/razor:0.01
docker run --rm -it --network=host -v $(pwd):/host:ro chenxiong/razor:0.01 /bin/bash
```

Next, place the benchmark in the appropriate directory.

```sh
mkdir benchmarks/debloat-eval
wget http://mirrors.ocf.berkeley.edu/gnu/gzip/gzip-1.12.tar.gz -O benchmarks/debloat-eval/gzip-1.12.tar.gz
cd benchmarks/debloat-eval
tar xf gzip-1.12.tar.gz
```

Then, build gzip.

```sh
cd gzip-1.12
./configure
make
```

Next, we create the `.orig` binary, as per the instructions in the last
section.  We also copy over the pre-created run_razor.py from the host, and
the logo.png file which is used by the tests.

```sh
cp gzip gzip.orig`
cp /host/run_razor.gzip-1.12.py run_razor.py
cp /host/logo.png logo.png
```

In run_razor.py, we modified the `train_run` function to use our `gzip.orig`
binary:

```py
def train_run(arg):
    BIN = './gzip.orig'
    cmd = BIN + ' ' + arg
    cmd = DRRUN + ' -c ' + CLIENT + ' -- ' + cmd
    execute(cmd)
```

We also modified the `train` function to to run a single test, the compression
of logo.png:

```py
def train():
    train_run("logo.png")
    return
```

Finally, in the main funtion we call the debloat function with the binary name
(without `.orig`):

```py
    elif sys.argv[1] == 'debloat':
        debloat('logs', 'gzip')
```

You can run `diff run_razor.gzip-1.12.py run_razor.grep-2.19.py` to see exactly
what was changed to get the script working with our new gzip benchmark.

With our edited `run_razor.py`, we can now run razor.

```sh
# This first step creates the trace
python run_razor.py train
# This second step uses the trace data to debloat the binary
python run_razor.py debloat
```

Now we can test the debloated binary:

```sh
# Get a fresh copy of logo.png and remove the output from the tests
cp /host/logo.png logo.png
rm logo.png.gz
# Run the debloated binary:
gzip.orig_temp/gzip.orig.debloated logo.png
```
