echo "enter ext"
read ext
echo "enter dest"
read dest
mkdir -p "$dest"
for file in *"$ext"; do
[ -f "$file" ] && cp "$file" "$dest"
done
