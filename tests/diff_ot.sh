#!/bin/bash
while [ ${#1} -gt 0 ]; do
	echo "testing file $1..."
	./ft_otool $1 &> diff1
	otool -t $1 &> diff2
	diff diff1 diff2 > res
	read diff < res
	if [ ${#diff} -gt 0 ]; then
#		echo $1
		echo -e "\033[31mdiff found in file $1\033[0m"
	fi
	rm diff1 diff2 res
	shift
done
