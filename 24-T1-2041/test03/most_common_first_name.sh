#!/bin/dash
cut -d'|' -f3 |  sed 's/.*, //g' |  cut -d' ' -f1 | sort | uniq -c | sort -n | sed 's/[1-9]//g' | sed 's/ //g' | tail -n1