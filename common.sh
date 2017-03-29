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

retrive_challenge() {
    local rc
    pushd $(dirname ${BASH_SOURCE[0]})/lib/ >/dev/null
    curl 'https://ringzer0team.com/challenges/'$QID -H 'Referer: https://ringzer0team.com/challenges' | node parser.js | dos2unix
    rc=$?
    popd >/dev/null
    return $rc
}

retrive_code_block() {
    local keyword="$1"
    local write_code=false
    while read -r line; do
        if [[ $line == "----- BEGIN "$keyword" -----" ]]; then
            write_code=true
            continue
        elif [[ $line == "----- END "$keyword" -----" ]]; then
            return
        fi

        if $write_code; then
            echo "$line"
        fi
    done
}

override curl func_curl
QID=$(basename $(dirname $(readlink -f ${BASH_SOURCE[1]})))
