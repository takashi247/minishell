#!/bin/bash

# USAGE ##################
#
# all test
# ./pwdtest.sh
#
# all test with leaks
# ./pwdtest.sh leaks
#
# make only
# ./pwdtest.sh make
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
CYAN=$(printf '\033[36m')
RESET=$(printf '\033[0m')

WORKDIR=`pwd`

printf "${YELLOW}%s${RESET}\n" "[mini] pwd"
export PWD=hello
./builtin.out pwd
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] pwd"
export PWD=hello
pwd
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] pwd ~"
./builtin.out pwd ~
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] pwd ~"
pwd ~
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] pwd \"~\""
./builtin.out pwd "~"
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] pwd \"~\""
pwd "~"
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] pwd \"\""
./builtin.out pwd ""
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] pwd \"\""
pwd ""
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] pwd ''"
./builtin.out pwd ''
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] pwd ''"
pwd ''
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] pwd \$HOME"
./builtin.out pwd $HOME
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] pwd \$HOME"
pwd $HOME
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] pwd hoge"
./builtin.out pwd hoge
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] pwd hoge"
pwd hoge
echo $?
echo

printf "${CYAN}%s${RESET}\n" "mkdir pwdtest"
mkdir pwdtest
printf "${YELLOW}%s${RESET}\n" "[mini] pwd; cd pwdtest; pwd"
./builtin.out cd_pwd pwdtest
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
./builtin.out cd_pwd pwdtest
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
./builtin.out cd_pwd pwdtest
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
./builtin.out pwd hoge world
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] pwd hoge world"
pwd hoge world
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] pwd -"
./builtin.out pwd -
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] pwd -"
pwd -
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] pwd --"
./builtin.out pwd --
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] pwd --"
pwd --
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] pwd -a"
./builtin.out pwd -a
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] pwd -a"
pwd -a
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] pwd -- -a"
./builtin.out pwd -- -a
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] pwd -- -a"
pwd -- -a
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] pwd --version"
./builtin.out pwd --version
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] pwd --version"
pwd --version
echo $?
echo

rm -rf pwdtest
