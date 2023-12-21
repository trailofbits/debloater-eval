#!/bin/bash
set -e
# eval.yml
# 15-20
timeout 12h pipenv run differ --verbose samples/pdftohtml/eval.yml 2>&1 | tee reports/pdftohtml-eval.log
timeout 12h pipenv run differ --verbose samples/sort-8.16/eval.yml 2>&1 | tee reports/sort-eval.log
timeout 12h pipenv run differ --verbose samples/chown-8.2/eval.yml 2>&1 | tee reports/chown-eval.log
timeout 12h pipenv run differ --verbose samples/objdump/eval.yml 2>&1 | tee reports/objdump-eval.log
timeout 12h pipenv run differ --verbose samples/nmap/eval.yml 2>&1 | tee reports/nmap-eval.log
# eval-aggressive.yml
# 11-20
timeout 12h pipenv run differ -r reports-aggressive --verbose samples/uniq-8.16/eval-aggressive.yml 2>&1 | tee reports/uniq-eval-aggressive.log
timeout 12h pipenv run differ -r reports-aggressive --verbose samples/date-8.21/eval-aggressive.yml 2>&1 | tee reports/date-eval-aggressive.log
timeout 12h pipenv run differ -r reports-aggressive --verbose samples/bftpd-6.1/eval-aggressive.yml 2>&1 | tee reports/bftpd-eval-aggressive.log
timeout 12h pipenv run differ -r reports-aggressive --verbose samples/make/eval-aggressive.yml 2>&1 | tee reports/make-eval-aggressive.log
timeout 12h pipenv run differ -r reports-aggressive --verbose samples/imagemagick/eval-aggressive.yml 2>&1 | tee reports/imagemagick-eval-aggressive.log
timeout 12h pipenv run differ -r reports-aggressive --verbose samples/pdftohtml/eval-aggressive.yml 2>&1 | tee reports/pdftohtml-eval-aggressive.log
timeout 12h pipenv run differ -r reports-aggressive --verbose samples/sort-8.16/eval-aggressive.yml 2>&1 | tee reports/sort-eval-aggressive.log
timeout 12h pipenv run differ -r reports-aggressive --verbose samples/chown-8.2/eval-aggressive.yml 2>&1 | tee reports/chown-eval-aggressive.log
timeout 12h pipenv run differ -r reports-aggressive --verbose samples/objdump/eval-aggressive.yml 2>&1 | tee reports/objdump-eval-aggressive.log
timeout 12h pipenv run differ -r reports-aggressive --verbose samples/nmap/eval-aggressive.yml 2>&1 | tee reports/nmap-eval-aggressive.log
