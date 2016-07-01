#!/bin/bash

# Please enter the complete path of the directory where u have you lem-in
SH_DIR='..'
#

function timeout() { perl -e 'alarm shift; exec @ARGV' "$@"; }

end()
{
	echo "\nTEST WITH SUCESS : \033[36;1m $TOTAL_OK \033[0m/ $TOTAL_TEST"

	rm -rf "1" " 2>&-" ">&toto" \> 2\>\&- \>\> pwd titi toto truc ../.a* \& \&hoho 12 123 123123123 123asd 2 3 a ab abc abcdefg asd123 @\ toto z zb .a*
	echo "\nPlease report any bug to mressier@student.42.fr"
}

compile_project()
{
	make -C $SH_DIR && return 1
	return 0
}

print_title()
{
	echo "\033[34m***************************************************************\033[0m\n"
	echo "\033[34m \t\t\t$1\t \033[0m\n"
}

test_big_fail()
{
	ret=0
	if [ -n "$content" ]
	then
		ret=1
		segfault=`cat error_file | grep -i "Segmentation fault"`
		bus_error=`cat error_file | grep -i "bus error"`
		abort=`cat error_file | grep -i "abort"`
		echo "\033[36m\c"
		if [ -n "$segfault" ]
		then
			echo "\t[  SEG  ]\033[0m"
		elif [ -n "$bus_error" ]
		then
			echo "\t[  BUS  ]\033[0m"
		elif [ -n "$abort" ]
		then
			echo "\t[  ABRT  ]\033[0m"
		else
			ret=0
		fi
	fi
	echo "\033[0m\c"
	return $ret
}

print_success_or_not()
{
	if [ $1 -eq 1 ]
	then
		echo "\t[  \033[32mOK\033[0m  ]\c"
	else
		echo "\t[  \033[31mFAIL\033[0m  ]\c"
	fi
}

get_success_value()
{
	content=`cat $1`
	if [ -z "$content" ]
	then
		return 1
	else
		return 0
	fi
}

print_success()
{
	get_success_value $1
	print_success_or_not $?
}

# $1 contient le fichier
# $2 contient le nom du shell

delete_shell_ref()
{
	cat $1 | sed "s/^$2://g" > tmp
	mv tmp $1
}

# $1 : shell

delete_shells_references()
{
	delete_shell_ref "$file_check_error" "$1"
	delete_shell_ref "$file_check" "$1"
	delete_shell_ref 'test_error' "shell"
	delete_shell_ref 'test_valid' "shell"
}

# Le dernier shell de la liste est utilisé par défaut si aucun autre ne match

test_shells()
{
	let "TOTAL_TEST++"
	for shell in 'sh' 'csh' 'ksh' 'tcsh' 'bash' 'zsh'
	do
		file_check="sh_valid"
		file_check_error="sh_error"
		$shell < $1/$3 > $file_check 2>$file_check_error
		delete_shells_references $shell
		diff -i test_valid $file_check > get_diff_stdout
		diff -i test_error $file_check_error > get_diff_stderr
		get_success_value 'get_diff_stdout'
		success=$?
		if [ $success -eq 1 ] || [ $shell = 'zsh' ]
		then
			print_success 'get_diff_stdout'
			print_success 'get_diff_stderr'
			if [ $success -eq 1 ]
			then
				echo " -> match with [\033[32m$shell\033[0m]"
				let "TOTAL_OK++"
			else
				echo " \033[31m unmatch \033[0m"
			fi
			break
		fi
	done
}

test_with_files()
{
	file_check="$2/$3"
	file_check_error="$2/error_$3"
	diff -i test_valid $file_check > get_diff_stdout
	get_success_value 'get_diff_stdout'
	success=$?
	let "TOTAL_TEST++"
	if [ $success -eq 1 ]
	then
		let "TOTAL_OK++"
	fi
	print_success 'get_diff_stdout'
	if [ -e "$file_check_error" ]
	then
		diff -i $file_check_error test_error > get_diff_stderr
		print_success 'get_diff_stderr'
	fi
	echo ""
}

# $1 => contient le nom du dossier avec les fichiers
# $2 => contient le nom du dossier avec les fichiers de verifications
# $3 => contient le nom du fichier testé

test_fichier()
{
	exist=0
	if [ -e "$2/$3" ]
	then
		exist=1
	fi
	if [ $exist -eq 0 ]
	then
		test_shells $1 $2 $3
	else
		test_with_files $1 $2 $3
	fi
}

# $1 => variable contenant les fichiers
# $2 => variable contenant le nom du dossier contenant les fichiers
# $3 => contient le directory des fichiers à diff

test_files()
{
	for file in $1
	do
		$SH_DIR/42sh < $2/$file 2>test_error > test_valid
		pb=$?
		echo "$file" ": \c"
		test_fichier $2 $3 $file
	done
}

# $1 : contient le dossier dans lequel recuperer les noms de fichier

get_all_files()
{
	files=$(ls $1)
	if [ -z "$files" ]
	then
		return 0
	fi
	files=$(echo $files | sort -)
	files=$(echo $files | tr " " "\n")
	return 1
}

# $1 is the dir where to find maps
# $2 contain dir with file to diff
# $3 is the title of the sequence
new_test()
{
	print_title "$3"
	echo "\t\t  STDOUT\t\t STDERR\n"
	dir_files_to_test=$1
	echo "\033[36mDir : " $dir_files_to_test/ "\033[0m"
	get_all_files $dir_files_to_test
	if [ $? -eq 1 ]
	then
		test_files "$files" "$dir_files_to_test" "$2"
	fi
}

#
# MAIN
#

TOTAL_OK=0
TOTAL_TEST=0
if [ $? ] && [ $# == 0 ]
then
	compile_project
	echo "\n"
	new_test "minishell_tests" "check_minishell_tests" "MINISHELL TESTS"
	new_test "pipe_test" "check_pipe_test" "PIPE TESTS"
	new_test "redir_test" "check_redir_test" "REDIRECTIONS TESTS"
	new_test "pipe_redir" "check_pipe_redir" "PIPE AND REDIR TESTS"
	new_test "builtin_test" "check_builtin_test" "BUILTIN TESTS"
	new_test "et_ou_test" "check_et_ou_test" "ET (&&) OU (||) TESTS"
	new_test "subshell_test" "check_subshell_test" "SUBSHELL TESTS"
	new_test "globbing_test" "check_globbing_test" "GLOBBING TESTS"
	end
fi
if [ $# -gt 0 ] && [ $1 = "clean" ]
then
	echo "\n\033[36mClean files...\033[0m "
	rm -rf get_diff_stdout get_diff_stderr sh_error sh_valid test_error test_valid
	make -C $SH_DIR fclean
fi
