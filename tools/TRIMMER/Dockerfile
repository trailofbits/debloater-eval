FROM ubuntu:16.04

RUN DEBIAN_FRONTEND=noninteractive apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y \
    build-essential \
    cmake \
    git \
    gettext \
    gnutls-dev \
    groff-base \
    libbz2-dev \
    libevent-dev \
    libidn11-dev \
    libmemcached-tools \
    libpcap-dev \
    libpcre3-dev \
    libssl-dev \
    pkg-config \
    python-minimal \
    uuid-dev \
    wget \
    wireless-tools \
    curl \
    autopoint \
    bison \
    gperf \
    texinfo \ 
    python3
ENV TRIMMER_HOME=/root/Trimmer
RUN cd `dirname $TRIMMER_HOME` && \
    git clone https://github.com/ashish-gehani/Trimmer.git && \
    cp $TRIMMER_HOME/vagrants/16.04/bash_profile .bash_profile 
RUN cd /root && . /root/.bash_profile && \
    curl "https://bootstrap.pypa.io/pip/2.7/get-pip.py" -o "get-pip.py" && \
    python get-pip.py && \
    pip install wllvm && \
    mkdir $LLVM_HOME && \
    cd $LLVM_HOME && \
    wget https://releases.llvm.org/7.0.0/llvm-7.0.0.src.tar.xz && \
    wget https://releases.llvm.org/7.0.0/cfe-7.0.0.src.tar.xz && \
    wget https://releases.llvm.org/7.0.0/compiler-rt-7.0.0.src.tar.xz && \
    tar xvf llvm-7.0.0.src.tar.xz && \
    tar xvf cfe-7.0.0.src.tar.xz && \
    tar xvf compiler-rt-7.0.0.src.tar.xz && \
    mv compiler-rt-7.0.0.src compiler-rt && \
    mv cfe-7.0.0.src/ llvm-7.0.0.src/tools/clang && \
    mkdir llvm-7.0.0.obj && \
    cd llvm-7.0.0.obj && \
    cmake -DCMAKE_BUILD_TYPE=MinSizeRel -DLLVM_ENABLE_PROJECTS=compiler-rt ../llvm-7.0.0.src && \
    make -j16 && \
    make install && \
    git clone https://github.com/SVF-tools/SVF && \
    cd SVF && \
    git checkout 0b75f3e0c10db04d65b6eafd91da5da9be71ecaa && \
    sed -i '/set(CMAKE_CXX_FLAGS "-std=gnu++11 -O3 -fno-rtti")/c\\t\tset(CMAKE_CXX_FLAGS "-std=gnu++11 -O3 -fno-rtti -fPIC")' CMakeLists.txt && \
    sed -i '/set(CMAKE_CXX_FLAGS "-std=gnu++11 -O0 -fno-rtti")/c\\t\tset(CMAKE_CXX_FLAGS "-std=gnu++11 -O0 -fno-rtti -fPIC")' CMakeLists.txt && \
    sed -i '/set_target_properties(Cudd PROPERTIES COMPILE_FLAGS "-Wno-format -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast -O3 -w -DHAVE_IEEE_754 -DSIZEOF_VOID_P=8 -DSIZEOF_LONG=8")/c\set_target_properties(Cudd PROPERTIES COMPILE_FLAGS "-Wno-format -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast -O3 -w -DHAVE_IEEE_754 -DSIZEOF_VOID_P=8 -DSIZEOF_LONG=8 -fPIC")' lib/CUDD/CMakeLists.txt && \
    sed -i '/set_target_properties(LLVMCudd PROPERTIES COMPILE_FLAGS "-Wno-format -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast -O3 -w -DHAVE_IEEE_754 -DSIZEOF_VOID_P=8 -DSIZEOF_LONG=8")/c\set_target_properties(LLVMCudd PROPERTIES COMPILE_FLAGS "-Wno-format -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast -O3 -w -DHAVE_IEEE_754 -DSIZEOF_VOID_P=8 -DSIZEOF_LONG=8 -fPIC")' lib/CUDD/CMakeLists.txt && \
    mkdir Release-build && \
    cd Release-build && \
    cmake .. && \
    make -j16 && \
    make install && \
    cd ../include/ && \
    cp -r * /usr/local/include/ && \
    cd $TRIMMER_HOME && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make