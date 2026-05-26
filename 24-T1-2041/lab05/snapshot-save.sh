#!/bin/dash

count=0
for file in .*; do
    FileName="$(echo $file | cut -d'.' -f2)"
    if [ "$FileName" = "snapshot" ]; then
        count=$((count + 1))
    fi
done

dirName=".snapshot.$count"
echo "Creating snapshot $count"
mkdir $dirName
for file in *; do
    if [ "$file" = "snapshot-save.sh" ]; then
        continue
    fi
    if [ "$file" = "snapshot-load.sh" ]; then
        continue
    fi

    cp "$file" "$dirName"
done