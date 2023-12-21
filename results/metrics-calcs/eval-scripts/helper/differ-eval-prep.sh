# make templates for evaluation yaml files from originals
find samples -name "*.yml" -execdir sh -c "cp {} eval.yml" ";"
find samples -name "eval.yml" -execdir sh -c "sed -i 's/link_filename:.*/&.symlink/' eval.yml" ";"
find samples -name "eval.yml" -execdir sh -c "cp {} eval-buster.yml" ";"
