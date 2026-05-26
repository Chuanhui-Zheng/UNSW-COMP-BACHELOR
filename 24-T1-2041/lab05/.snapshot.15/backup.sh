#!/bin/dash

max=-1
for file in $(ls -a . | grep -E "$1"); do

    if [ "$file" = "$1" ]; then
        continue
    else
        newFileNum=$(echo "$file" | cut -d'.' -f4)
        if [ "$newFileNum" -gt "$max" ]; then
            max="$newFileNum"
        fi
    fi
done
max=$((max+1))
echo Backup of \'$1\' saved as \'.$1.$max\'
cp "$1" ".$1.$max"