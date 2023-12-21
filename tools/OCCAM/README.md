## OCCAM
### Overview
According to its [github](https://github.com/lahiri-phdworks/OCCAM) it is a "...whole-program partial evaluator for LLVM bitcode that aims at debloating programs and shared/static libraries running in a specific deployment context."

### Debloat Instructions
1. Pull and run the required image ``docker pull sricsl/occam:bionic;  docker run -v `pwd`:/host -it sricsl/occam:bionic``
2. Write the manifest. This page explains how to write an OCCAM manifest: https://github.com/SRI-CSL/OCCAM/wiki/Manifest
3. Compile the binary with gclang
4. Run `get-bc` on the built ls binary to get the compatible bitcode in the same directory as the manifest
4. Run `slash ./manifest.json` to get the debloated binary

### Example with gzip
1. Start a shell in a new container based on the image
```
docker pull sricsl/occam:bionic
docker run -v `pwd`:/host -it sricsl/occam:bionic
```
1. Download the source
```
wget https://mirrors.ocf.berkeley.edu/gnu/gzip/gzip-1.12.tar.gz
tar xf gzip-1.12.tar.gz
cd gzip-1.12
```
1. Write a manifest and save it as a json file in the home directory. Below is a working example for gzip
See the docs for writing an OCCAM manifest here: https://github.com/SRI-CSL/OCCAM/wiki/Manifest
```
{
    "main": "gzip.bc",
    "binary": "gzip-reduced",
    "modules": [],
    "name": "gzip",
    "static_args": ["-v", "-k"],
    "dynamic_args": "1"

}
```
1. Compile the binary with wllvm
```
CC=gclang CFLAGS="-O3 -fPIC -fPIE" LDFLAGS=-pie ./configure
make
```
1. Generate bitcode and move it to the same directory as the manifest file.
```
get-bc ./gzip
mv gzip.bc ~
cd ~
```
1. Run OCCAM with the manifest file
```
slash ./manifest.json
```
1. The reduced binary will be output in the same directory with the name `gzip-reduced`. It will have its decompression ability removed.
