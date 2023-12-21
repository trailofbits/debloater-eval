# Build Instructions

Build instructions for objdump

## Trimmer

```
apt install -y libgmp3-dev libmpfr-dev flex
cd source/binutils-gdb
FORCE_UNSAFE_CONFIGURE=1 CC=wllvm CXX=wllvm++ CFLAGS="-O0 -Xclang -disable-O0-optnone -fPIC -fPIE" CXXFLAGS="-O0 -Xclang -disable-O0-optnone -fPIC -fPIE" LDFLAGS="-pie" ./configure --disable-gcc-warnings
make
```


## OCCAM

Same as above, except use CC=gclang CXX=gclang++ CFLAGS='-O3 -fPIc -fPIE' CXXFLAGS='-O3 -fPIC -fPIE' LDFLAGS='-pie'

