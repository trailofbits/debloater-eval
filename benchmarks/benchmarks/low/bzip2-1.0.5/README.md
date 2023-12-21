# Build Instructions

## Trimmer

```
cd ./source/original
wllvm -pie -O0 -Xclang -disable-O0-optnone -fPIC -fPIE bzip2.c blocksort.c huffman.c crctable.c randtable.c compress.c decompress.c bzlib.c -o bzip2
```

## OCCAM

```
cd ./source/original
gclang -pie -O3 -fPIC -fPIE bzip2.c blocksort.c huffman.c crctable.c randtable.c compress.c decompress.c bzlib.c -o bzip2
```
NOTE: bzip2 does expose an option for compiling as a shared lib and thin interface as opposed to a monolith, but we build as a monolith to allow for consistent comparison across tools (TRIMMER and other tools cannot debloat shared libs at the same time as the main executable like OCCAM can) 

