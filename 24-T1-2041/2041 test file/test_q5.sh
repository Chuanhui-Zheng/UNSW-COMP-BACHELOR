#!/usr/bin/env dash

list=$(grep -E "$1" "$2" | cut -d'|' -f2 | sort | uniq)
head=$(echo "$list" | head -1)
tail=$(echo "$list" | tail -1)
for i in $(seq "$head" "$tail")
do
    if ! echo "$list" | grep -q $i
    then
        echo "$i"
    fi
done