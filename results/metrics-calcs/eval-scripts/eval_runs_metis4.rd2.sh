#!/bin/bash
set -x
mkdir -p reports-buster-rd2
export LD_LIBRARY_PATH="./debloater-eval.batch2/debloater-eval-binaries/benchmarks/high/poppler-0.60/binaries/buster/"
echo "Checking that libraries are present for all buster campaigns"
ldd_standard="$(python3 /home/metis4/metis-eval-private/scripts/ldd-check.py eval-buster.yml -v 2>&1 | grep 'missing library')"
if [[ -n $ldd_standard ]]; then 
    echo "Libraries missing for buster campaigns: $ldd_standard"
    exit 1
fi
echo "All libraries present"
set -e
#crashes
timeout 12h pipenv run differ -r reports-buster-rd2 --verbose samples/grep-2.19/eval-buster.yml 2>&1 | tee reports-buster-rd2/grep-eval-buster.log
timeout 12h pipenv run differ -r reports-buster-rd2 --verbose samples/uniq-8.16/eval-buster.yml 2>&1 | tee reports-buster-rd2/uniq-eval-buster.log
timeout 12h pipenv run differ -r reports-buster-rd2 --verbose samples/lighttpd/eval-buster.yml 2>&1 | tee reports-buster-rd2/lighttpd-eval-buster.log
timeout 12h pipenv run differ -r reports-buster-rd2 --verbose samples/nginx/eval-buster.yml 2>&1 | tee reports-buster-rd2/nginx-eval-buster.log
# missing libraries
timeout 12h pipenv run differ -r reports-buster-rd2 --verbose samples/pdftohtml/eval-buster.yml 2>&1 | tee reports-buster-rd2/pdftohtml-eval-buster.log
