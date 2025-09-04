echo "Enter filename"
read fi
if [ -d "$fi" ]; then
echo "It is directory"
elif [ -f "$fi" ]; then
echo "It is file and exists"
else
echo "Doesnt exists"
fi

