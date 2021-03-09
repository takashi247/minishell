#!/bin/bash

cd libft
make
cd ..
gcc -Wall -Wextra -Werror -I./includes -I./libft srcs/cd.c srcs/pwd.c srcs/command_utils.c srcs/env_utils.c -Llibft -lft -D CDTEST -o cd.out

YELLOW=$(printf '\033[33m')
RESET=$(printf '\033[0m')

WORKDIR=`pwd`

printf "${YELLOW}%s${RESET}\n" "./cd.out"
./cd.out
echo

printf "${YELLOW}%s${RESET}\n" "./cd.out cd"
./cd.out cd
echo

TEST3="~"
printf "${YELLOW}%s${RESET}\n" "[mini] cd ~"
./cd.out cd ~
printf "${YELLOW}%s${RESET}\n" "[bash] cd ~"
pwd
cd ~
pwd
cd $WORKDIR
echo

printf "${YELLOW}%s${RESET}\n" "[mini] cd \"~\""
./cd.out cd "~"
printf "${YELLOW}%s${RESET}\n" "[bash] cd \"~\""
pwd
cd "~"
pwd
cd $WORKDIR
echo

printf "${YELLOW}%s${RESET}\n" "[mini] cd \"\""
./cd.out cd ""
printf "${YELLOW}%s${RESET}\n" "[bash] cd \"\""
pwd
cd ""
pwd
cd $WORKDIR
echo

printf "${YELLOW}%s${RESET}\n" "[mini] cd ''"
./cd.out cd ''
printf "${YELLOW}%s${RESET}\n" "[bash] cd ''"
pwd
cd ''
pwd
cd $WORKDIR
echo

printf "${YELLOW}%s${RESET}\n" "[mini] cd \$HOME"
./cd.out cd $HOME
printf "${YELLOW}%s${RESET}\n" "[bash] cd \$HOME"
pwd
cd $HOME
pwd
cd $WORKDIR
echo

printf "${YELLOW}%s${RESET}\n" "[mini] cd hoge"
./cd.out cd hoge
printf "${YELLOW}%s${RESET}\n" "[bash] cd hoge"
pwd
cd hoge
pwd
echo
cd $WORKDIR

printf "${YELLOW}%s${RESET}\n" "mkdir cdtest"
mkdir cdtest
printf "${YELLOW}%s${RESET}\n" "[mini] cd cdtest"
./cd.out cd cdtest
printf "${YELLOW}%s${RESET}\n" "[bash] cd cdtest"
pwd
cd cdtest
pwd
echo
cd $WORKDIR

printf "${YELLOW}%s${RESET}\n" "[mini] cd \"cdtest\""
./cd.out cd "cdtest"
printf "${YELLOW}%s${RESET}\n" "[bash] cd \"cdtest\""
pwd
cd "cdtest"
pwd
echo
cd $WORKDIR

printf "${YELLOW}%s${RESET}\n" "[mini] cd \"cdtest \""
./cd.out cd "cdtest "
printf "${YELLOW}%s${RESET}\n" "[bash] cd \"cdtest \""
pwd
cd "cdtest "
pwd
echo
cd $WORKDIR

printf "${YELLOW}%s${RESET}\n" "[mini] cd hoge world"
./cd.out cd hoge world
printf "${YELLOW}%s${RESET}\n" "[bash] cd hoge world"
pwd
cd hoge world
pwd
echo
cd $WORKDIR

printf "${YELLOW}%s${RESET}\n" "[mini] cd hoge world"
./cd.out cd hoge world
printf "${YELLOW}%s${RESET}\n" "[bash] cd hoge world"
pwd
cd hoge world
pwd
echo
cd $WORKDIR

printf "${YELLOW}%s${RESET}\n" "[mini] cd -a"
./cd.out cd -a
printf "${YELLOW}%s${RESET}\n" "[bash] cd -a"
pwd
cd -a
pwd
echo
cd $WORKDIR

printf "${YELLOW}%s${RESET}\n" "mkdir ./-a"
mkdir ./-a
printf "${YELLOW}%s${RESET}\n" "[mini] cd ./-a"
./cd.out cd ./-a
printf "${YELLOW}%s${RESET}\n" "[bash] cd ./-a"
pwd
cd ./-a
pwd
echo
cd $WORKDIR
rm -rf ./-a

printf "${YELLOW}%s${RESET}\n" "[mini] cd -a cdtest"
./cd.out cd -a cdtest
printf "${YELLOW}%s${RESET}\n" "[bash] cd -a cdtest"
pwd
cd -a cdtest
pwd
echo
cd $WORKDIR

printf "${YELLOW}%s${RESET}\n" "[mini] cd --version cdtest"
./cd.out cd --version cdtest
printf "${YELLOW}%s${RESET}\n" "[bash] cd --version cdtest"
pwd
cd --version cdtest
pwd
echo
cd $WORKDIR

printf "${YELLOW}%s${RESET}\n" "[mini] cd --"
./cd.out cd --
printf "${YELLOW}%s${RESET}\n" "[bash] cd --"
pwd
cd --
pwd
echo
cd $WORKDIR

printf "${YELLOW}%s${RESET}\n" "[mini] cd -- cdtest"
./cd.out cd -- cdtest
printf "${YELLOW}%s${RESET}\n" "[bash] cd -- cdtest"
pwd
cd -- cdtest
pwd
echo
cd $WORKDIR

rm -rf cdtest
