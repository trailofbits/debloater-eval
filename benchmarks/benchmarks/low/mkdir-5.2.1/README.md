# Build Instructions

## Trimmer

```
cd source/original
CC=wllvm CXX=wllvm++ CFLAGS="-O0 -Xclang -disable-O0-optnone -fPIC -fPIE" CXXFLAGS="-O0 -Xclang -disable-O0-optnone -fPIC -fPIE" LDFLAGS="-pie" FORCE_UNSAFE_CONFIGURE=1 ./configure
sed -i '127s/static int/int/' ./src/test.c
sed -i '34s/tee/tee2/' ./src/tee.c
sed -i '161s/tee/tee2/' ./src/tee.c
sed -i '149s/tee/tee2/' ./src/tee.c
make
```
