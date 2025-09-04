for file in "$@"; do
if [ -f "$file" ]; then
rm "$file"
echo "removed"
else
echo "not found"
fi
done

