#!/bin/bash

# USAGE ##################
#
# all test
# ./exittest.sh
#
# all test with leaks
# ./exittest.sh leaks
#
# make only
# ./exittest.sh make
#
##########################

if [ "$1" = "leaks" ]; then
    make bltest # LEAK TEST
else
    make btest
fi

if [ "$1" = "make" ]; then
    exit
fi

YELLOW=$(printf '\033[33m')
RESET=$(printf '\033[0m')

WORKDIR=`pwd`

printf "${YELLOW}%s${RESET}\n" "./builtin.out"
./builtin.out
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit"
./builtin.out exit
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit"
echo "exit" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit ~"
./builtin.out exit ~
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit ~"
echo "exit ~" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit \"~\""
./builtin.out exit "~"
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit \"~\""
echo "exit \"~\"" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit \"\""
./builtin.out exit ""
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit \"\""
echo "exit \"\"" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit ''"
./builtin.out exit ''
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit ''"
echo "exit ''" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit \$HOME"
./builtin.out exit $HOME
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit \$HOME"
echo "exit $HOME" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit hoge"
./builtin.out exit hoge
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit hoge"
echo "exit hoge" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit hoge world"
./builtin.out exit hoge world
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit hoge world"
echo "exit hoge world" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit -"
./builtin.out exit -
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit -"
echo "exit -" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit -a"
./builtin.out exit -a
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit -a"
echo "exit -a" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit --version"
./builtin.out exit --version
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit --version"
echo "exit --version" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit 1"
./builtin.out exit 1
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit 1"
echo "exit 1" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit 3"
./builtin.out exit 3
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit 3"
echo "exit 3" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit 0"
./builtin.out exit 0
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit 0"
echo "exit 0" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit +100"
./builtin.out exit +100
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit +100"
echo "exit +100" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit -1"
./builtin.out exit -1
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit -1"
echo "exit -1" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit --1"
./builtin.out exit --1
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit --1"
echo "exit --1" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit --"
./builtin.out exit --
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit --"
echo "exit --" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit -- \"   5   \""
./builtin.out exit -- "   5   "
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit -- \"   5   \""
echo "exit -- \"   5   \"" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit a"
./builtin.out exit a
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit a"
echo "exit a" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit 255"
./builtin.out exit 255
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit 255"
echo "exit 255" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit 300"
./builtin.out exit 300
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit 300"
echo "exit 300" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit 2147483647"
./builtin.out exit 2147483647
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit 2147483647"
echo "exit 2147483647" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit 2147483650"
./builtin.out exit 2147483650
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit 2147483650"
echo "exit 2147483650" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit 9223372036854775807"
./builtin.out exit 9223372036854775807
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit 9223372036854775807"
echo "exit 9223372036854775807" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit 9223372036854775808"
./builtin.out exit 9223372036854775808
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit 9223372036854775808"
echo "exit 9223372036854775808" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit -9223372036854775808"
./builtin.out exit -9223372036854775808
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit -9223372036854775808"
echo "exit -9223372036854775808" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit -9223372036854775809"
./builtin.out exit -9223372036854775809
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit -9223372036854775809"
echo "exit -9223372036854775809" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit 21A"
./builtin.out exit 21A
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit 21A"
echo "exit 21A" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit 1 2 3"
./builtin.out exit 1 2 3
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit 1 2 3"
echo "exit 1 2 3" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit 10 a b"
./builtin.out exit 10 a b
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit 10 a B"
echo "exit 10 a b" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit a 20"
./builtin.out exit a 20
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit a 20"
echo "exit a 20" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit \"   5   \""
./builtin.out exit "   5   "
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit \"   5   \""
echo "exit \"   5   \"" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit \"   5 6  \""
./builtin.out exit "   5 6   "
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit \"   5 6  \""
echo "exit \"   5 6   \"" | bash
echo $?
echo
