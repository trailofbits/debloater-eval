#!/bin/bash
# eval_runs_buster 11-19
timeout 12h pipenv run differ -r reports-buster --verbose samples/uniq-8.16/eval-buster.yml 2>&1 | tee reports-buster/uniq-eval-buster.log
timeout 12h pipenv run differ -r reports-buster --verbose samples/date-8.21/eval-buster.yml 2>&1 | tee reports-buster/date-eval-buster.log
timeout 12h pipenv run differ -r reports-buster --verbose samples/bftpd-6.1/eval-buster.yml 2>&1 | tee reports-buster/bftpd-eval-buster.log
timeout 12h pipenv run differ -r reports-buster --verbose samples/make/eval-buster.yml 2>&1 | tee reports-buster/make-eval-buster.log
timeout 12h pipenv run differ -r reports-buster --verbose samples/pdftohtml/eval-buster.yml 2>&1 | tee reports-buster/pdftohtml-eval-buster.log
timeout 12h pipenv run differ -r reports-buster --verbose samples/sort-8.16/eval-buster.yml 2>&1 | tee reports-buster/sort-eval-buster.log
timeout 12h pipenv run differ -r reports-buster --verbose samples/chown-8.2/eval-buster.yml 2>&1 | tee reports-buster/chown-eval-buster.log
timeout 12h pipenv run differ -r reports-buster --verbose samples/objdump/eval-buster.yml 2>&1 | tee reports-buster/objdump-eval-buster.log
timeout 12h pipenv run differ -r reports-buster --verbose samples/nmap/eval-buster.yml 2>&1 | tee reports-buster/nmap-eval-buster.log
