#!/bin/dash
if [ $# -eq 2 ]; then
    num="$1"
    string="$2"
    if ! echo $num | grep -qE '^[0-9]+$'; then
        echo './echon.sh: argument 1 must be a non-negative integer'
    else
        i=0
        while [ $i -lt $num ]; do
            echo $string
            i=$((i+1))
        done
    fi
else 
    echo "Usage: ./echon.sh <number of lines> <string>" 1>&2
    exit 1
fi