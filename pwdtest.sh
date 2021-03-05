#!/bin/bash

cd libft
make
cd ..
gcc -Wall -Wextra -Werror -I./includes -I./libft srcs/cd.c srcs/pwd.c srcs/command_utils.c srcs/env_utils.c -Llibft -lft -D PWDTEST -o pwd.out

YELLOW=$(printf '\033[33m')
RESET=$(printf '\033[0m')

WORKDIR=`pwd`

printf "${YELLOW}%s${RESET}\n" "./pwd.out"
./pwd.out
echo

printf "${YELLOW}%s${RESET}\n" "[mini] pwd"
export PWD=hello
./pwd.out pwd
printf "${YELLOW}%s${RESET}\n" "[bash] pwd"
export PWD=hello
pwd
echo

printf "${YELLOW}%s${RESET}\n" "[mini] pwd ~"
./pwd.out pwd ~
printf "${YELLOW}%s${RESET}\n" "[bash] pwd ~"
pwd ~
echo

printf "${YELLOW}%s${RESET}\n" "[mini] pwd \"~\""
./pwd.out pwd "~"
printf "${YELLOW}%s${RESET}\n" "[bash] pwd \"~\""
pwd "~"
echo

printf "${YELLOW}%s${RESET}\n" "[mini] pwd \"\""
./pwd.out pwd "~"
printf "${YELLOW}%s${RESET}\n" "[bash] pwd \"\""
pwd ""
echo

printf "${YELLOW}%s${RESET}\n" "[mini] pwd ''"
./pwd.out pwd ''
printf "${YELLOW}%s${RESET}\n" "[bash] pwd ''"
pwd ''
echo

printf "${YELLOW}%s${RESET}\n" "[mini] pwd \$HOME"
./pwd.out pwd $HOME
printf "${YELLOW}%s${RESET}\n" "[bash] pwd \$HOME"
pwd $HOME
echo

printf "${YELLOW}%s${RESET}\n" "[mini] pwd hoge"
./pwd.out pwd hoge
printf "${YELLOW}%s${RESET}\n" "[bash] pwd hoge"
pwd hoge
echo

printf "${YELLOW}%s${RESET}\n" "mkdir pwdtest"
mkdir pwdtest
printf "${YELLOW}%s${RESET}\n" "[mini] pwd; cd pwdtest; pwd"
./pwd.out cd pwdtest
printf "${YELLOW}%s${RESET}\n" "[bash] pwd; cd pwdtest; pwd"
pwd
cd pwdtest
pwd
echo
cd $WORKDIR

printf "${YELLOW}%s${RESET}\n" "[mini] pwd hoge world"
./pwd.out pwd hoge world
printf "${YELLOW}%s${RESET}\n" "[bash] pwd hoge world"
pwd hoge world
echo

printf "${YELLOW}%s${RESET}\n" "[mini] pwd -"
./pwd.out pwd -
printf "${YELLOW}%s${RESET}\n" "[bash] pwd -"
pwd -
echo

printf "${YELLOW}%s${RESET}\n" "[mini] pwd -a"
./pwd.out pwd -a
printf "${YELLOW}%s${RESET}\n" "[bash] pwd -a"
pwd -a
echo

printf "${YELLOW}%s${RESET}\n" "[mini] pwd --version"
./pwd.out pwd --version
printf "${YELLOW}%s${RESET}\n" "[bash] pwd --version"
pwd --version
echo

rm -rf pwdtest
