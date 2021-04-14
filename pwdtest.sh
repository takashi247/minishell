#!/bin/bash

cd libft
make bonus
cd ..
gcc -g -Wall -Wextra -Werror -I./includes -I./libft srcs/cd.c srcs/pwd.c srcs/exit.c srcs/env.c srcs/unset.c srcs/export.c srcs/command_utils.c srcs/env_utils.c -Llibft -lft -D PWDTEST -o pwd.out

YELLOW=$(printf '\033[33m')
CYAN=$(printf '\033[36m')
RESET=$(printf '\033[0m')

WORKDIR=`pwd`

printf "${YELLOW}%s${RESET}\n" "./pwd.out"
./pwd.out
echo

printf "${YELLOW}%s${RESET}\n" "[mini] pwd"
export PWD=hello
./pwd.out pwd
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] pwd"
export PWD=hello
pwd
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] pwd ~"
./pwd.out pwd ~
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] pwd ~"
pwd ~
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] pwd \"~\""
./pwd.out pwd "~"
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] pwd \"~\""
pwd "~"
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] pwd \"\""
./pwd.out pwd ""
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] pwd \"\""
pwd ""
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] pwd ''"
./pwd.out pwd ''
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] pwd ''"
pwd ''
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] pwd \$HOME"
./pwd.out pwd $HOME
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] pwd \$HOME"
pwd $HOME
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] pwd hoge"
./pwd.out pwd hoge
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] pwd hoge"
pwd hoge
echo $?
echo

printf "${CYAN}%s${RESET}\n" "mkdir pwdtest"
mkdir pwdtest
printf "${YELLOW}%s${RESET}\n" "[mini] pwd; cd pwdtest; pwd"
./pwd.out cd pwdtest
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] pwd; cd pwdtest; pwd"
pwd
cd pwdtest
pwd
echo $?
echo
cd $WORKDIR
rm -rf pwdtest

printf "${CYAN}%s${RESET}\n" "mkdir pwdtest"
mkdir pwdtest
printf "${CYAN}%s${RESET}\n" "unset PWD"
unset PWD
printf "${YELLOW}%s${RESET}\n" "[mini] pwd; cd pwdtest; pwd"
./pwd.out cd pwdtest
echo $?
printf "${CYAN}%s${RESET}\n" "unset PWD"
unset PWD
printf "${YELLOW}%s${RESET}\n" "[bash] pwd; cd pwdtest; pwd"
pwd
cd pwdtest
pwd
echo $?
echo
cd $WORKDIR
rm -rf pwdtest

printf "${CYAN}%s${RESET}\n" "mkdir pwdtest"
mkdir pwdtest
printf "${CYAN}%s${RESET}\n" "export PWD=/Users"
export PWD=/Users
printf "${YELLOW}%s${RESET}\n" "[mini] pwd; cd pwdtest; pwd"
./pwd.out cd pwdtest
echo $?
printf "${CYAN}%s${RESET}\n" "export PWD=/Users"
export PWD=/Users
printf "${YELLOW}%s${RESET}\n" "[bash] pwd; cd pwdtest; pwd"
pwd
cd pwdtest
pwd
echo $?
echo
cd $WORKDIR
rm -rf pwdtest

printf "${YELLOW}%s${RESET}\n" "[mini] pwd hoge world"
./pwd.out pwd hoge world
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] pwd hoge world"
pwd hoge world
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] pwd -"
./pwd.out pwd -
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] pwd -"
pwd -
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] pwd --"
./pwd.out pwd --
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] pwd --"
pwd --
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] pwd -a"
./pwd.out pwd -a
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] pwd -a"
pwd -a
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] pwd -- -a"
./pwd.out pwd -- -a
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] pwd -- -a"
pwd -- -a
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] pwd --version"
./pwd.out pwd --version
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] pwd --version"
pwd --version
echo $?
echo

rm -rf pwdtest
