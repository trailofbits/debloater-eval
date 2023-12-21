# Build Instructions

## Trimmer

```
cd source/make
autoreconf -i
FORCE_UNSAFE_CONFIGURE=1 CC=wllvm CFLAGS="-O0 -Xclang -disable-O0-optnone -fPIC -fPIE" LDFLAGS="-pie" ./configure
make make
```
