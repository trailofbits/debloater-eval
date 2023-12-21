## TRIMMER

### Build Instructions

Build the docker image using the local Dockerfile.

```
docker build . --network=host
```

### Debloat Instructions

1. Start a bash prompt in the container as a login shell

```
docker run --rm --network=host -it ${IMAGE_ID} /bin/bash -l
```

1. Compile source with the `wllvm` tool as the compiler and then extract its bitcode with the `extract-bc` tool.
1. Configure with disabling warnings, optimizations, and debug flags

```
FORCE_UNSAFE_CONFIGURE=1 CC=wllvm CFLAGS="-O0 -Xclang -disable-O0-optnone" ./configure --disable-gcc-warnings
```

1. Build the binary via `make`.
1. Copy the binary to a new, empty directory
1. Extract the bitcode with `extract-bc`
1. Write the manifest json file.
1. Create a working directory for trimmer `mkdir working_dir`
1. Run trimmer on it with `python ${TRIMMER_HOME}/tool/trimmer.py <mainfest filepath> ./working_dir`
1. The reduced binary is saved in `./working_dir/<value provided to binary key in manifest>`

### Example with ls

This debloater can't run successfully against gzip, so instead of the standard example, we'll use the ls utility from coreutils instead.

1. Start a bash prompt in the container as a login shell

```
docker run --rm --network=host -it ${IMAGE_ID} /bin/bash -l
```

1. Clone coreutils repo and checkout tag `v8.25`

```
git clone https://github.com/coreutils/coreutils.git
git checkout tags/v8.25
```

1. Install deps `apt install -y autopoint bison gperf texinfo autoconf automake`
1. Run `./bootstrap`
1. Make sure the required env's are setConfigure with disabling warnings, optimizations, and debug flags

```
FORCE_UNSAFE_CONFIGURE=1 CC=wllvm CFLAGS="-O0 -Xclang -disable-O0-optnone" ./configure --disable-gcc-warnings
```

1. Build ls `make`. The make command may fail. If it does, run `make src/ls` to build the ls binary only.
1. Copy the ls binary to a new, empty directory

```
mkdir ~/new_empty_dir
cp src/ls ~/new_empty_dir
```

1. Extract the bitcode with `extract-bc ls`
1. Write manifest json file and save it to a path I will refer to as `${LS_MANIFEST}`. See 
[Trimmer's README](https://github.com/ashish-gehani/Trimmer#description-of-manifest-file) 
for documentation on the manifest file.  Example used:

```
    {
        "main" : "ls.bc",
        "binary": "lsfin",
        "modules": [],
        "name": "ls-test",
        "args": ["-l"],
        "native_libs": [],
        "config_files": [],
        "ldflags": []
    }
```

1. Create a working directory for trimmer `mkdir working_dir`
1. Run trimmer on it with `python ${TRIMMER_HOME}/tool/trimmer.py ${LS_MANIFEST} ./working_dir`
1. Run the reduced binary at `./working_dir/lsfin`
