echo -n "Enter a number 1 or string Hello or character A"
read c
case $c in
1) echo "entered 1";;
"Hello") echo "entered hello";;
'A') echo "entered three";;
*) echo "invalid"
esac

