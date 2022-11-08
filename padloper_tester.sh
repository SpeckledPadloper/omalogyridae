
RESET="\033[0m"
RED="\033[31m"
GREEN="\033[32m"

asciichar()
{
	LC_CTYPE=C printf '%d' "'$1"
}

printascii()
{
	for (( i=0; i<${#1}; i++ )); do
		C1=$(asciichar "${1:$i:1}")
		C2=$(asciichar "${2:$i:1}")
		echo $C1 $C2
#		echo "${1:$i:1} ${2:$i:1}"
	done
}

funtion()
{
	RES1=$(echo $@ | bash 2>/dev/null)
	RETURN1=$?
	RES2=$(echo $@ | ./minishell 2>/dev/null)
#	printascii "$RES1" "$RES2"
	RETURN2=$?

	if [[ "$RES1" == "$RES2" ]]
	then
		echo 
		printf $GREEN"yay output\n"$RESET
		#echo Bash out: $RES1
		#echo Mini out: $RES2
	else
		echo 
		printf $RED"nay output\n"$RESET
		echo Bash out: $RES1
		echo Mini out: $RES2
	fi
	
	if [[ "$RETURN1" == "$RETURN2" ]]
	then
		echo
		printf $GREEN"yay exit_code\n"$RESET
		#echo Bash: $RETURN1
		#echo Mini: $RETURN2
	else
		echo
		printf $RED"nay exit_code\n"$RESET
		#echo Bash: $RETURN1
		#echo Mini: $RETURN2
	fi
	echo

}

error_fun()
{
	RES1=$(echo $@ | bash 2>/dev/null)
	RETURN1=$?
	RES2=$(echo $@ | ./minishell 2>/dev/null)
	RETURN2=$?

	RES1=$(echo $@ | bash 2>&1 | cut -c 15-)
	RES2=$(echo $@ | ./minishell 2>&1 | tail -n 1 | cut -c 18-)
	
	if [[ "$RES1" == "$RES2" ]]
	then
		echo 
		printf $GREEN"yay output\n"$RESET
		#echo Bash out: $RES1
		#echo Mini out: $RES2
	else
		echo 
		printf $RED"nay output\n"$RESET
		echo Bash out: $RES1
		echo Mini out: $RES2
		#printascii "$RES1" "$RES2"
	fi

	if [[ "$RETURN1" == "$RETURN2" ]]
	then
		echo
		printf $GREEN"yay exit_code\n"$RESET
		#echo Bash: $RETURN1
		#echo Mini: $RETURN2
	else
		echo
		printf $RED"nay exit_code\n"$RESET
		echo Bash: $RETURN1
		echo Mini: $RETURN2
	fi
	echo
}	



funtion 'echo -n -n -n hallo'
funtion 'echo'
funtion 'echo hallo hallo -n'
funtion 'echo -n hallo'
funtion 'ls  -la | wc'
funtion 'echo hoi | cat -e | cat -e | cat -e'
funtion '< Makefile cat -e | cat -e'
funtion '< Makefile cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e'
funtion 'export | grep PATH'
funtion 'exit 500'

echo ----------------errors-----------------

error_fun 'lsfjslkj'
error_fun '<k'
error_fun '<a'
error_fun './a'
error_fun 'ls | wc > out_noright'
error_fun 'cd dir_noright'
error_fun 'cd Makefile'
error_fun 'cd blabla'
error_fun 'export 6'
error_fun 'unset hoi='
error_fun 'exit hoi'
error_fun 'exit 89 978'