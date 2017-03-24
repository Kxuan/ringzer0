. $(dirname ${BASH_SOURCE[0]})/config

override() {
    local bin func

    bin="$1"
    func="$2"
    
    eval "
$bin() {
    unset $bin

    $func \"\$@\"

    override \"$bin\" \"$func\"
}"
}

func_curl() {
    for i; do
        if [[ "$i" == *PHPSESSID* ]]; then
            echo "CURL STOP! FOUND PHPSESSID" >&2
            exit 127
        fi
    done
    local -a args=()
    if [[ -n $CURL_VERBOSE ]]; then
        args+=(-v)
    fi
    curl "${args[@]}" -s -A "RingZer0/0.1" -H 'Cookie: PHPSESSID='$PHPSESSID "$@"
}

override curl func_curl
QID=$(basename $(dirname $(readlink -f ${BASH_SOURCE[1]})))
