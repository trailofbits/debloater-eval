# Build Instructions

## Trimmer

```
cd source/merged
wllvm -O0 -Xclang -disable-O0-optnone -fPIC -fPIE -pie -o gzip gzip-1.2.4.c.origin.c
```

## OCCAM

```
cd source/original
CC=gclang CFLAGS='-O3 -fPIC -fPIE -pie' ./configure
make
```
NOTE: I'm not sure what issues we ran into building with wllvm, but gllvm handled this one just fine from the original source (newly added).


