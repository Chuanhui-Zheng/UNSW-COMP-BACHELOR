#!/bin/bash
courses=$(curl --location --silent http://www.timetable.unsw.edu.au/2024/"$1"KENS.html)
echo "$courses" | grep '<td' | grep "$1" | sed 's/<td class="data"><a href=".*">//g' |
 sed 's/<\/a><\/td>//g' | sed -E "s/^                                       //g" | sed 'N;s/\n/ /' | 
 sort | uniq