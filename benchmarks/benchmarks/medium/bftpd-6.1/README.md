# Build Instructions

## Trimmer

To get a position independent executable you will have to edit the Makefile produced by the configure and assign `-pie` to the `LDFLAGS=` variable declared at the top.

```
cd source/bftpd
FORCE_UNSAFE_CONFIGURE=1 CC=wllvm CFLAGS="-O0 -Xclang -disable-O0-optnone -fPIE" LDFLAGS=-pie ./configure --disable-gcc-warnings
CC=wllvm make
```

## OCCAM

Same as above, except need to edit Makefile to use -O3 -fPIC -fPIE instead of flags above. need to pass CC=gclang to make instead of wllvm.

