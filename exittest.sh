#!/bin/bash

cd libft
make bonus
cd ..
gcc -g -Wall -Wextra -Werror -I./includes -I./libft srcs/cd.c srcs/pwd.c srcs/exit.c srcs/env.c srcs/unset.c srcs/export.c srcs/command_utils.c srcs/env_utils.c -Llibft -lft -D EXITTEST -o exit.out

YELLOW=$(printf '\033[33m')
RESET=$(printf '\033[0m')

WORKDIR=`pwd`

printf "${YELLOW}%s${RESET}\n" "./exit.out"
./exit.out
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit"
./exit.out exit
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit"
echo "exit" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit ~"
./exit.out exit ~
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit ~"
echo "exit ~" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit \"~\""
./exit.out exit "~"
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit \"~\""
echo "exit \"~\"" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit \"\""
./exit.out exit ""
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit \"\""
echo "exit \"\"" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit ''"
./exit.out exit ''
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit ''"
echo "exit ''" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit \$HOME"
./exit.out exit $HOME
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit \$HOME"
echo "exit $HOME" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit hoge"
./exit.out exit hoge
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit hoge"
echo "exit hoge" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit hoge world"
./exit.out exit hoge world
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit hoge world"
echo "exit hoge world" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit -"
./exit.out exit -
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit -"
echo "exit -" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit -a"
./exit.out exit -a
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit -a"
echo "exit -a" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit --version"
./exit.out exit --version
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit --version"
echo "exit --version" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit 1"
./exit.out exit 1
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit 1"
echo "exit 1" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit 3"
./exit.out exit 3
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit 3"
echo "exit 3" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit 0"
./exit.out exit 0
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit 0"
echo "exit 0" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit 9223372036854775807"
./exit.out exit 9223372036854775807
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit 9223372036854775807"
echo "exit 9223372036854775807" | bash
echo $?
echo

# TODO: 未対応
echo "※今後対応予定です"
printf "${YELLOW}%s${RESET}\n" "[mini] exit 9223372036854775808"
./exit.out exit 9223372036854775808
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit 9223372036854775808"
echo "exit 9223372036854775808" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit +100"
./exit.out exit +100
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit +100"
echo "exit +100" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit -1"
./exit.out exit -1
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit -1"
echo "exit -1" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit --1"
./exit.out exit --1
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit --1"
echo "exit --1" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit --"
./exit.out exit --
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit --"
echo "exit --" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit -- \"   5   \""
./exit.out exit -- "   5   "
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit -- \"   5   \""
echo "exit -- \"   5   \"" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit a"
./exit.out exit a
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit a"
echo "exit a" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit 255"
./exit.out exit 255
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit 255"
echo "exit 255" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit 300"
./exit.out exit 300
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit 300"
echo "exit 300" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit 2147483647"
./exit.out exit 2147483647
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit 2147483647"
echo "exit 2147483647" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit 2147483650"
./exit.out exit 2147483650
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit 2147483650"
echo "exit 2147483650" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit 21A"
./exit.out exit 21A
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit 21A"
echo "exit 21A" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit 1 2 3"
./exit.out exit 1 2 3
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit 1 2 3"
echo "exit 1 2 3" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit 10 a b"
./exit.out exit 10 a b
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit 10 a B"
echo "exit 10 a b" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit a 20"
./exit.out exit a 20
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit a 20"
echo "exit a 20" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit \"   5   \""
./exit.out exit "   5   "
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit \"   5   \""
echo "exit \"   5   \"" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] exit \"   5 6  \""
./exit.out exit "   5 6   "
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] exit \"   5 6  \""
echo "exit \"   5 6   \"" | bash
echo $?
echo
