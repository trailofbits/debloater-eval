# prepare batch2 for scripts 
mkdir debloater-eval.batch2
cp debloater-eval-binaries.batch2.zip debloater-eval.batch2
cd debloater-eval.batch2
unzip debloater-eval-binaries.batch2.zip
find debloater-eval-binaries -name chisel-2-binaries.tar.gz -execdir sh -c "mkdir chisel-2-binaries && tar -xzf chisel-2-binaries.tar.gz -C chisel-2-binaries" ";"
find debloater-eval-binaries -name chisel-1-binaries.tar.gz -execdir sh -c "mkdir chisel-1-binaries && tar -xzf chisel-1-binaries.tar.gz -C chisel-1-binaries" ";"
find debloater-eval-binaries/ -name libfilter.tar.gz -execdir sh -c "mkdir libfilter && tar -xzf libfilter.tar.gz -C libfilter" ";"
# symlink to help ldd
find debloater-eval-binaries -name libMagickWand-7.Q16HDRI.so.0.0.0 -execdir sh -c "ln -s libMagickWand-7.Q16HDRI.so.0.0.0 libMagickWand-7.Q16HDRI.so.0" ";"
find debloater-eval-binaries -name libMagickCore-7.Q16HDRI.so.0.0.0 -execdir sh -c "ln -s libMagickCore-7.Q16HDRI.so.0.0.0 libMagickCore-7.Q16HDRI.so.0" ";"
