echo "enter filename"
read file
sed -n 'p;n' "$file"

