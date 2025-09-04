read a b
if [ $a == $b ]; then
echo "$a equals $b"
elif [ $a -gt $b ]; then
echo "$a greater thanm $b"
elif ((a<b)); then
echo "$a less than $b"
else
echo "None"
fi

