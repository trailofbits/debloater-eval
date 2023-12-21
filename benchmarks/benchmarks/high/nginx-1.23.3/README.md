# Build Instructions

## Trimmer

To get a position independent executable you will need to edit `source/nginx/objs/Makefile` after configuring. You need to append `-pie` to the end of the value of the `LINK =` variable declared on line 4.

```
cd source/nginx
FORCE_UNSAFE_CONFIGURE=1 CC=wllvm CFLAGS="-Xclang -disable-O0-optnone -O0 -fPIC -fPIE" CXX=wllvm++ CXX_FLAGS="-Xclang -disable-O0-optnone -O0 -fPIC -fPIE" LDFLAGS=-pie ./auto/configure
make
```
