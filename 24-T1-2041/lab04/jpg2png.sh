#!/bin/dash
for file in *.jpg; do
    newfile=$(echo "$file" | sed "s/.jpg/.png/")
    if [ -e "$newfile" ]
    then
        echo "$newfile already exists"
        break
    else
        convert "$file" "$newfile" 2>dev>null
        rm "$file"
    fi
done