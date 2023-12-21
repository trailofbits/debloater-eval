# Build Instructions

## Trimmer

```
apt install -y libfreetype6-dev libfontconfig1-dev libnss3-dev libjpeg-dev libtiff-dev libopenjpeg-dev
cd source/poppler
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=release -DCMAKE_C_FLAGS="-O0 -Xclang -disable-O0-optnone -fPIC -fPIE" -DCMAKE_CXX_FLAGS="-O0 -Xclang -disable-O0-optnone -fPIC -fPIE" -E env -DCMAKE_CXX_COMPILER="wllvm++ -pie" -DCMAKE_C_COMPILER=wllvm ..
make pdftohtml
```
