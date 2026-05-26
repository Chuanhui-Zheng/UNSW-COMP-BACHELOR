#!/bin/dash
for file in *.htm*; do
    prefix="$(echo $file | cut -d'.' -f2)"
    if [ $prefix = "html" ]; then
        continue
    fi
    fileName=$(echo "$file" | cut -d'.' -f1)
    if [ -f "$fileName.html" ]; then
        echo "$fileName.html exists"
        exit 1
    else
        mv "$file" "$fileName.html"
    fi
done