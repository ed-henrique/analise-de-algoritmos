shuf -i "$1-$2" -n $3 -r -o "a-$3.txt"
sort -n a.txt > "o-$3.txt"
sort -r -n a.txt > "d-$3.txt"
