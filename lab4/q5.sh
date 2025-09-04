pattern=$1
file=$2
while true; do
echo "Menu"
echo "1.Search"
echo "2. Delete"
echo "3. Exit"
read -p "Enter choice: " choice
case $choice in 
1) grep "$pattern" "$file"
;;
2) sed -i "s/$pattern//g" "$file"
echo "deleted"
;;
3) echo "Exiting..."
exit 0
;;
esac
done

