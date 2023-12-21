# remove all eval.yml and eval-buster.yml files
if [[ "$1" == "REMOVE" ]]; then
    find samples -name "eval.yml" -execdir sh -c "rm eval.yml" ";"
    find samples -name "eval-buster.yml" -execdir sh -c "rm eval-buster.yml" ";"
fi