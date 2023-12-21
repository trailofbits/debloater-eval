# Build Instructions

## Trimmer

```
cd source/nmap
FORCE_UNSAFE_CONFIGURE=1 CC="wllvm -Xclang -disable-O0-optnone" CFLAGS="-O0 -fPIC -fPIE" CXX="wllvm++ -Xclang -disable-O0-optnone" CXXFLAGS="-O0 -fPIC -fPIE" LDFLAGS="-pie" ./configure
make
```
