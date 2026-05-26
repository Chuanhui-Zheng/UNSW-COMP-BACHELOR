#!/bin/dash
start=$1
end=$2
file=$3
while [ "$start" -le "$end" ]; do
    echo "$start" >>"$file"
    start=$((start + 1))
done