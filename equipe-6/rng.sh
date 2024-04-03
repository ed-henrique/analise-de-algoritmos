shuf -i "$1-$2" -n $3 -r -o "a-$3.txt"
sort -n "a-$3.txt" > "o-$3.txt"
sort -r -n "a-$3.txt" > "d-$3.txt"
