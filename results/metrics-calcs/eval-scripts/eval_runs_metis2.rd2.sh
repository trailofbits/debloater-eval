#!/bin/bash
# Note: should run with bash to contain environment variable changes
set -x
mkdir -p reports-rd2
LD_LIBRARY_PATH="./debloater-eval.batch2/debloater-eval-binaries/benchmarks/high/poppler-0.60/binaries/64/"
LD_LIBRARY_PATH="$LD_LIBRARY_PATH:./debloater-eval.batch2/debloater-eval-binaries/benchmarks/high/imagemagick-7.0.1-0/binaries/64"
LD_LIBRARY_PATH="$LD_LIBRARY_PATH:/home/metis2/bionic-libs/manual"
LD_LIBRARY_PATH="$LD_LIBRARY_PATH:/home/metis2/xenial-libs/manual"
export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:/home/metis2/fossa-libs/manual"
echo "Checking that libraries are present for all campaigns"
ldd_standard="$(python3 /home/metis2/metis-eval-private/scripts/ldd-check.py eval.yml -v 2>&1 | grep 'missing library')"
if [[ -n $ldd_standard ]]; then 
    echo "Libraries missing for standard campaigns: $ldd_standard"
    exit 1
fi
ldd_aggressive=$(python3 /home/metis2/metis-eval-private/scripts/ldd-check.py eval-aggressive.yml -v 2>&1 | grep "missing library")
if [[ -n $ldd_aggressive ]]; then 
    echo "Libraries missing for aggressive campaigns: $ldd_aggressive"
    exit 1 
fi
echo "All libraries present"
set -e
# crashes
timeout 12h pipenv run differ -r reports-rd2 --verbose samples/grep-2.19/eval.yml 2>&1 | tee reports-rd2/grep-eval.log
timeout 12h pipenv run differ -r reports-rd2-aggressive --verbose samples/grep-2.19/eval-aggressive.yml 2>&1 | tee reports-rd2/grep-eval-aggressive.log
# run tar trimmer manually
#timeout 12h pipenv run differ -r reports-rd2-aggressive --verbose samples/tar-1.14/eval-aggressive.yml 2>&1 | tee reports-rd2/tar-eval-aggressive.log
timeout 12h pipenv run differ -r reports-rd2-aggressive --verbose samples/lighttpd/eval-aggressive.yml 2>&1 | tee reports-rd2/lighttpd-eval-aggressive.log
timeout 12h pipenv run differ -r reports-rd2 --verbose samples/nginx/eval.yml 2>&1 | tee reports-rd2/nginx-eval.log
timeout 12h pipenv run differ -r reports-rd2-aggressive --verbose samples/nginx/eval-aggressive.yml 2>&1 | tee reports-rd2/nginx-eval-aggressive.log
# missing libraries
timeout 12h pipenv run differ -r reports-rd2 --verbose samples/wget/eval.yml 2>&1 | tee reports-rd2/wget-eval.log
timeout 12h pipenv run differ -r reports-rd2-aggressive --verbose samples/wget/eval-aggressive.yml 2>&1 | tee reports-rd2/wget-eval-aggressive.log
timeout 12h pipenv run differ -r reports-rd2-aggressive --verbose samples/objdump/eval-aggressive.yml 2>&1 | tee reports-rd2/objdump-eval-aggressive.log
timeout 12h pipenv run differ -r reports-rd2-aggressive --verbose samples/memcached/eval-aggressive.yml 2>&1 | tee reports-rd2/memcached-eval-aggressive.log
timeout 12h pipenv run differ -r reports-rd2-aggressive --verbose samples/nmap/eval-aggressive.yml 2>&1 | tee reports-rd2/nmap-eval-aggressive.log
timeout 12h pipenv run differ -r reports-rd2 --verbose samples/pdftohtml/eval.yml 2>&1 | tee reports-rd2/pdftohtml-eval.log
timeout 12h pipenv run differ -r reports-rd2-aggressive --verbose samples/pdftohtml/eval-aggressive.yml 2>&1 | tee reports-rd2/pdftohtml-eval-aggressive.log
timeout 12h pipenv run differ -r reports-rd2 --verbose samples/imagemagick/eval.yml 2>&1 | tee reports-rd2/imagemagick-eval.log
timeout 12h pipenv run differ -r reports-rd2-aggressive --verbose samples/imagemagick/eval-aggressive.yml 2>&1 | tee reports-rd2/imagemagick-eval-aggressive.log
