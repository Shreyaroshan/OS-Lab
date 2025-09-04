declare -a arrayOfNumber
j=0
for i in $@
do
arrayofNumber[j]=$i
((j++))
done
echo "{arrayOfNumber[@]}"


