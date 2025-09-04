find . -type f -name "*.txt" | while read file; do
newname="${file%.txt}.text"
mv "$file" "$newname"
done

