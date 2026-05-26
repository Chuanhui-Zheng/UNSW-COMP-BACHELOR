#!/bin/dash

for file in $@; do
    echo "$file"
    echo -n "Address to e-mail this image to? "
    read email
    echo -n "Message to accompany image? "
    read message
    echo "$message" | mutt -s "$file sent to $email" -e 'set copy=no' -a $file -- $email
    echo "$file sent to $email"
done
