# Build Instructions

## Trimmer

```
cd source/original
wllvm -pie -O0 -Xclang -disable-O0-optnone -fPIC -fPIE bzip2.c blocksort.c huffman.c crctable.c randtable.c compress.c decompress.c bzlib.c -o bzip2
```
