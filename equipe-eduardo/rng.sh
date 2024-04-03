shuf -i "$1-$2" -n $3 -r -o output_tmp.txt

if [[ $4 = "sort" ]]; then
  sort -n output_tmp.txt > output.txt
  rm output_tmp.txt
elif [[ $4 = "unsort" ]]; then
  sort -r -n output_tmp.txt > output.txt
  rm output_tmp.txt
else
  mv output_tmp.txt output.txt
fi
