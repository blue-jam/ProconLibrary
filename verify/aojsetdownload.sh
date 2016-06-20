#!/bin/bash

if [ $# -ne 1 ]; then
	echo "usage $0 [problem id] (number of testcases)"
	exit 1
fi

id=$1
num=50
if [ $# -ge 2 ]; then
	num=$2
fi
URL="http://analytic.u-aizu.ac.jp:8080/aoj/testcase.jsp?id=${id}&case=[%s]&type=%s"

num=$(curl --head -sw '"%{http_code}" "%{url_effective}"\n' \
   `printf $URL 1-$num "in"` \
   | grep ^\"200\" \
   | awk 'match($2,/case=[0-9]+/) {print substr($2,RSTART+5,RLENGTH-5)}' \
   | awk 'END {print NR}')


curl -o "#1.in" `printf $URL 1-$num "in"`
curl -o "#1.diff" `printf $URL 1-$num "out"`
