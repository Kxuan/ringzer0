lookup() {
    while read char code; do
        if [[ "$1" = "$code" ]]; then
            echo -n $char
            return
        fi
    done < code
    echo "Not Found"
}

while read code; do
lookup $code
done <answer
echo
