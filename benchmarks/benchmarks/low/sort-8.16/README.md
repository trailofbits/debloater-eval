# Build Instructions

## Trimmer

```
cd source/original/
FORCE_UNSAFE_CONFIGURE=1 CC=wllvm CFLAGS="-O0 -Xclang -disable-O0-optnone -fPIC -fPIE" LDFLAGS="-pie" ./configure --disable-gcc-warnings
make # This command will fail, but sort will be built
```
