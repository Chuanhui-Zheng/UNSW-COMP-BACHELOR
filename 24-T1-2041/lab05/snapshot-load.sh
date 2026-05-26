#!/bin/dash

snapshot-save.sh
echo "Restoring snapshot $1"
dirName=".snapshot.$1"

for file in "$dirName"/*; do
    cp $file .
done