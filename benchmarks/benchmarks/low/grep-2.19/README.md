# Build Instructions

## Trimmer

```
cd source/original
autoreconf
FORCE_UNSAFE_CONFIGURE=1 CC=wllvm CXX=wllvm++ CXXFLAGS="-O0 -Xclang -disable-O0-optnone -fPIC -fPIE" CFLAGS="-O0 -Xclang -disable-O0-optnone -fPIC -fPIE" LDFLAGS=-pie ./configure
make
```

## LMCAS

Add

```
__attribute__((noinline)) void klee_dump_memory(void) {}
```

on line 61 of bzip2-1.0.5.c.origin.c and

```
klee_dump_memory();
```

on line 2266. Then compile it with:

```
musl-gclang -O0 -Xclang -disable-O0-optnone -o bzip2 bzip2-1.0.5.c.origin.c
```
