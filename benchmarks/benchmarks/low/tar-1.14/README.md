# Build Instructions

## Trimmer

```
cd source/merged
CC=wllvm CXX=wllvm++ CFLAGS="-O0 -Xclang -disable-O0-optnone -fPIC -fPIE" CXXFLAGS="-O0 -Xclang -disable-O0-optnone -fPIC -fPIE" LDFLAGS="-pie" FORCE_UNSAFE_CONFIGURE=1 ./configure
make
```
