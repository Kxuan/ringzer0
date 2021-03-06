#!/bin/bash
. ../common.sh
get() {
curl 'https://ringzer0team.com/challenges/13' -H 'Referer: https://ringzer0team.com/challenges' > tmp
csrf=$(grep csrf tmp | cut -d\" -f6)
message=$(sed -e 's/<[^>]*>//g' tmp  | grep -A1 BEGIN | tail -n1 | cut -d$'\t' -f3 | dos2unix)
#body=$(grep -A1 BEGIN tmp | cut -d$'\x9'  -f3 | cut -d\< -f1 | tail -n1 )
}
post() {
curl 'https://ringzer0team.com/challenges/13/'$hash -H 'Referer: https://ringzer0team.com/challenges/13'
}

get
body=$(echo $message)
echo $body
hash=$(echo -n $body  | sha512sum | cut -d\  -f1)
echo $hash
post | grep -A2 challenge-wrapper

