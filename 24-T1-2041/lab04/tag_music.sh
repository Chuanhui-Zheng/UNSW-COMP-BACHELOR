#!/bin/dash
if [ $# -eq 1 ]&&[ "$1" = "music/*" ]; then
	echo "$@"
else
	for file in "$@"
	do
		echo "$file"
	done
fi | while read -r files; do
    folder="$(ls "$files")"
    echo "$folder" |
    while read -r name; do
        title="$(echo "$name" | sed 's/ - /~/g'| cut -d'~' -f2)"
        artist="$(echo "$name" |sed 's/ - /~/g'| cut -d'~' -f3 | sed 's/.mp3//g')"
        track="$(echo "$name" |sed 's/ - /~/g'| cut -d'~' -f1)"
        album="$(echo "$files" | sed 's/.*music\///g;s/^ //g;s/\/$//g')"
        year="$(echo "$files" | sed -E 's/.*, //g')"
        id3 -t "$title" "$files/$name" >/dev/null
        id3 -T "$track" "$files/$name" >/dev/null
        id3 -a "$artist" "$files/$name" >/dev/null
        id3 -A "$album" "$files/$name" >/dev/null
        id3 -y "$year" "$files/$name" >/dev/null
    done
done