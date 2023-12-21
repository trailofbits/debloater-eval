The git submodule for wget-1.20.3 uses bootstrap to build the distribution, but dependencies for bootstrap are missing on the LMCAS container.

Instead, get the distribution tarball for wget directly:

  wget https://ftp.gnu.org/gnu/wget/wget-1.20.3.tar.gz

And build it using configure and make along with the --without-ssl flag:

  CC=musl-gclang CFLAGS="-fPIC -fPIE -pie" LDFLAGS=-pie FORCE_UNSAFE_CONFIGURE=1 ./configure --without-ssl
  CC=musl-gclang CFLAGS="-fPIC -fPIE -pie" LDFLAGS=-pie FORCE_UNSAFE_CONFIGURE=1 make -j${nproc} -l${nproc}

Only the wget binary is included here. I couldn't find a bitcode file specifically for wget (.wget.o.bc or similar). The source is omitted due to size (~20M).
