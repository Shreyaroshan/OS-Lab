case $1 in 
-linecount) wc -l < "$2"
;;
-wordcount) wc -w < "$2"
;;
-charcount) wc -c < "$2"
;;
esac
