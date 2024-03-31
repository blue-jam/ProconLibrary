#!/bin/bash

cd verify
python3 download.py

files=$(ls)
for project in $files; do
    if [ -d $project ]; then
        pushd $project
        if [ -e PROJECT ]; then
            rime test
            if [ $? != 0 ]; then
                echo "Failed test for ${project}"
                exit 1
            fi
        fi
        popd
    fi
done
