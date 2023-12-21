# Build Instructions

## Trimmer

```
cd source/original
CC=wllvm CXX=wllvm++ CFLAGS="-O0 -Xclang -disable-O0-optnone -fPIC -fPIE -D__need_getopt=1" CXXFLAGS="-O0 -Xclang -disable-O0-optnone -fPIC -fPIE" LDFLAGS="-pie" FORCE_UNSAFE_CONFIGURE=1 ./configure
make
```
