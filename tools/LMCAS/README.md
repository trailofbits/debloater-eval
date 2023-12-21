# LMCAS-METIS

## Overview

Uses a spec and modifications to a source to debloat it.

## Setup

If not already signed in to the docker tpcp server, you'll have to login.

```
$> docker login docker.tpcp.io
Username: <your user name>
Password: <gitlab tpcp access token with read permissions>
```

If already signed in to the docker tpcp server, the command below will download the container and run a shell in the
container

```
docker pull docker.tpcp.io/metis/lmcas/lmcas-deliv:2023-04-10@sha256:7875dabb6e10adac4087f31dc503143a3f3e20a5be1ce2920f1e62ad5f7969c5
```

The container provides documentation as a web page you may run like this:
`docker run --rm -itp 12345:80 --network=host docker.tpcp.io/metis/lmcas/lmcas-deliv:2023-04-10@sha256:7875dabb6e10adac4087f31dc503143a3f3e20a5be1ce2920f1e62ad5f7969c5 serve-docs`

### Debloat Instructions

Tabacco includes a component, Neck Miner, which automatically and heuristically identifies necks. In this release, this component is in a relatively immature state. There is currently no user interaction available for this tool and it cannot yet be run independently of Tabacco. When first attempting to debloat, you may skip step 1. If the Neck Miner fails to mark the neck, Tabacco will fail. You should then attempt to place the neck manually (Step 1) and proceed as before with Steps 2 through 4.

1. Place the neck and its declaration in the source. The target binary must have a "neck" inserted in the source that marks the transition from configuration to the main functionality during execution. This "neck" is

```
_lmcas_neck();
```

and it's declared at the top of the file as

```
__attribute__((noinline)) void _lmcas_neck(void) {}
```

2. Compile the source with the musl-gclang compiler residing in the image:

```
CC=musl-gclang CFLAGS="-fPIC -fPIE -pie" LDFLAGS=-pie FORCE_UNSAFE_CONFIGURE=1 ./configure
CC=musl-gclang CFLAGS="-fPIC -fPIE -pie" LDFLAGS=-pie FORCE_UNSAFE_CONFIGURE=1 make -j${nproc} -l${nproc}
```

Step 3: Write the spec and save it as a json file. The instructions for this are found in the LMCAS tool readme found within the container.
Step 4: Run Tabacco

```
tabacco -o debloated spec.json
```

## Example with gzip

1. Start shell with the image with a volume in the debloater-eval repo from the root directory of the repo

```
docker run --rm -itv $(pwd):/debloater-eval docker.tpcp.io/metis/lmcas/lmcas-deliv:2023-04-10@sha256:7875dabb6e10adac4087f31dc503143a3f3e20a5be1ce2920f1e62ad5f7969c5
```

2. Clone source into container. Because there is not package manager in the lmcas image, I mounted the current directory as a volume in the image and downloaded the source on my host to the same directory with

```
wget https://mirrors.ocf.berkeley.edu/gnu/gzip/gzip-1.12.tar.gz
tar xf gzip-1.12.tar.gz
```

3. (The Neck Miner succeeds in placing a neck automatically for gzip-1.12, so you may skip this step.) Declare the neck function by adding this to line 158 in gzip.c

```
__attribute__((noinline)) void _lmcas_neck(void) {}
```

4. Place the neck at line 655 in gzip.c
   The target binary must have a "neck" inserted in the source that marks the transition from configuration to the main functionality during execution. This "neck" is

```
_lmcas_neck();
```

5. Compile the source with the musl-gclang compiler residing in the image:

```
CC=musl-gclang CFLAGS="-fPIC -fPIE -pie" LDFLAGS=-pie FORCE_UNSAFE_CONFIGURE=1 ./configure
CC=musl-gclang CFLAGS="-fPIC -fPIE -pie" LDFLAGS=-pie FORCE_UNSAFE_CONFIGURE=1 make -j${nproc} -l${nproc}
```

6. Write the spec and save it as a .json file.  Below is an example to only
keep the compression functionality of gzip.  In order to write your own spec
file, please consult the documentation.

```
{
    "binary": "/here/gzip-1.12/gzip",
    "args": [
      "gzip",
      "-v"
    ],
    "env": {
      "CWD": "/",
      "PATH": ""
    },
    "cwd": "/"
  }
```

7. Run Tabacco

```
tabacco -o debloated <spec file>
```
