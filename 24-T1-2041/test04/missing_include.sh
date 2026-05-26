#!/bin/dash
for file in "$@"; do
    for header in $(cat "$file" | grep "#include" | cut -d' ' -f2 | grep -v '<' | sed 's/"//g'); do
        if [ ! -e "$header" ]; then
            echo "$header included into $file does not exist"
        fi
    done
done