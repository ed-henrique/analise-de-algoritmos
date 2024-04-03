shuf -i "$1-$2" -n $3 -r -o a.txt
sort -n a.txt > o.txt
sort -r -n a.txt > d.txt
