#!/bin/bash
while [ ${#1} -gt 0 ]; do
	echo "testing file $1..."
	./ft_nm $1 &> diff3
	nm $1 &> diff4
	diff diff3 diff4 > res2
	read diff < res2
	if [ ${#diff} -gt 0 ]; then
#		echo $1
		echo -e "\033[31mdiff found in file $1\033[0m"
	fi
	rm diff3 diff4 res2
	shift
done
