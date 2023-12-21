#!/bin/bash
set -e
timeout 12h pipenv run differ --verbose samples/tar-1.14/eval.yml 2>&1 | tee reports/tar-eval.log
timeout 12h pipenv run differ --verbose samples/bzip2-1.0.5/eval.yml 2>&1 | tee reports/bzip2-eval.log
timeout 12h pipenv run differ --verbose samples/nginx/eval.yml 2>&1 | tee reports/nginx-eval.log
timeout 12h pipenv run differ --verbose samples/uniq-8.16/eval.yml 2>&1 | tee reports/uniq-eval.log
timeout 12h pipenv run differ --verbose samples/date-8.21/eval.yml 2>&1 | tee reports/date-eval.log
