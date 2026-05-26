#!/bin/dash
small=""
medium=""
big=""
for file in * 
do
    count=$(wc -l "$file" | cut -f1 -d' ' 2>/dev/null)
    if [ -n "$count" ]; then
        if [ "$count" -lt 10 ]; then 
            small="$small $file"
        elif [ "$count" -ge 10 ] && [ "$count" -le 100 ]; then 
            medium="$medium $file"
        elif [ "$count" -gt 100 ]; then 
            big="$big $file"
        fi
    fi
done

small=$(echo "$small" | sed 's/^ //')
medium=$(echo "$medium" | sed 's/^ //')
big=$(echo "$big" | sed 's/^ //')
echo -n "Small files: $small"
echo ""

echo -n "Medium-sized files: $medium"
echo ""

echo -n "Large files: $big"
echo ""
