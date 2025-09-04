echo "Enter two val"
read a b
echo "enter op"
read op
((a++))
result=`echo "$a$op$b" | bc -l`
echo "Result of performing $a $op $b is $result"

