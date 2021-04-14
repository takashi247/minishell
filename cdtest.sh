#!/bin/bash

cd libft
make bonus
cd ..
gcc -g -Wall -Wextra -Werror -I./includes -I./libft srcs/cd.c srcs/pwd.c srcs/exit.c srcs/env.c srcs/unset.c srcs/export.c srcs/command_utils.c srcs/env_utils.c -Llibft -lft -D CDTEST -o cd.out

YELLOW=$(printf '\033[33m')
CYAN=$(printf '\033[36m')
RESET=$(printf '\033[0m')

WORKDIR=`pwd`
echo ""

# 引数なし
echo "※minishellではパスを引数に取らない場合invalid"
printf "${CYAN}%s${RESET}\n" "pwd:
${WORKDIR}"
printf "${YELLOW}%s${RESET}\n" "[mini] cd"
./cd.out cd
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] cd"
echo "cd" | bash
echo $?
echo "pwd" | bash
echo

# 引数特殊 ~ (シェルスクリプトによりminishellのテストも ~ が変数展開されている)
printf "${CYAN}%s${RESET}\n" "pwd:
${WORKDIR}"
printf "${YELLOW}%s${RESET}\n" "[mini] cd ~"
./cd.out cd ~
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] cd ~"
cd ~
echo $?
pwd
printf "PWD: ${PWD}\n"
printf "OLDPWD: ${OLDPWD}\n"
cd $WORKDIR
echo

# cd "~"
printf "${CYAN}%s${RESET}\n" "pwd:
${WORKDIR}"
printf "${YELLOW}%s${RESET}\n" "[mini] cd \"~\""
./cd.out cd "~"
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] cd \"~\""
cd "~"
echo $?
cd $WORKDIR
echo

# cd ""
printf "${CYAN}%s${RESET}\n" "pwd:
${WORKDIR}"
printf "${YELLOW}%s${RESET}\n" "[mini] cd \"\""
./cd.out cd ""
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] cd \"\""
cd ""
echo $?
pwd
printf "PWD: ${PWD}\n"
printf "OLDPWD: ${OLDPWD}\n"
cd $WORKDIR
echo

# cd ''
printf "${CYAN}%s${RESET}\n" "pwd:
${WORKDIR}"
printf "${YELLOW}%s${RESET}\n" "[mini] cd ''"
./cd.out cd ''
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] cd ''"
cd ''
echo $?
pwd
printf "PWD: ${PWD}\n"
printf "OLDPWD: ${OLDPWD}\n"
cd $WORKDIR
echo

# cd $HOME
printf "${CYAN}%s${RESET}\n" "pwd:
${WORKDIR}"
printf "${YELLOW}%s${RESET}\n" "[mini] cd \$HOME"
./cd.out cd $HOME
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] cd \$HOME"
cd $HOME
echo $?
pwd
printf "PWD: ${PWD}\n"
printf "OLDPWD: ${OLDPWD}\n"
cd $WORKDIR
echo

# cd hoge (No such file or directory)
printf "${CYAN}%s${RESET}\n" "pwd:
${WORKDIR}"
printf "${YELLOW}%s${RESET}\n" "[mini] cd hoge"
./cd.out cd hoge
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] cd hoge"
cd hoge
echo $?
cd $WORKDIR
echo

# cd cdtest
printf "${CYAN}%s${RESET}\n" "pwd:
${WORKDIR}"
printf "${YELLOW}%s${RESET}\n" "mkdir cdtest"
mkdir cdtest
printf "${YELLOW}%s${RESET}\n" "[mini] cd cdtest"
./cd.out cd cdtest
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] cd cdtest"
cd cdtest
echo $?
pwd
printf "PWD: ${PWD}\n"
printf "OLDPWD: ${OLDPWD}\n"
cd $WORKDIR
rm -rf cdtest
echo

# cd "cdtest"
printf "${CYAN}%s${RESET}\n" "pwd:
${WORKDIR}"
printf "${YELLOW}%s${RESET}\n" "mkdir cdtest"
mkdir cdtest
printf "${YELLOW}%s${RESET}\n" "[mini] cd \"cdtest\""
./cd.out cd "cdtest"
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] cd \"cdtest\""
cd "cdtest"
echo $?
pwd
printf "PWD: ${PWD}\n"
printf "OLDPWD: ${OLDPWD}\n"
cd $WORKDIR
rm -rf cdtest
echo

# cd "cdtest "
printf "${CYAN}%s${RESET}\n" "pwd:
${WORKDIR}"
printf "${YELLOW}%s${RESET}\n" "mkdir cdtest"
mkdir cdtest
printf "${YELLOW}%s${RESET}\n" "[mini] cd \"cdtest \""
./cd.out cd "cdtest "
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] cd \"cdtest \""
cd "cdtest "
echo $?
cd $WORKDIR
rm -rf cdtest
echo

# cd "cdtest"
printf "${CYAN}%s${RESET}\n" "pwd:
${WORKDIR}"
printf "${YELLOW}%s${RESET}\n" "mkdir cdtest"
mkdir cdtest
printf "${YELLOW}%s${RESET}\n" "[mini] cd cdtest hoge"
./cd.out cd cdtest hoge
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] cd cdtest hoge"
cd cdtest hoge
echo $?
pwd
printf "PWD: ${PWD}\n"
printf "OLDPWD: ${OLDPWD}\n"
cd $WORKDIR
rm -rf cdtest
echo

# cd "hoge world"
printf "${CYAN}%s${RESET}\n" "pwd:
${WORKDIR}"
printf "${YELLOW}%s${RESET}\n" "[mini] cd hoge world"
./cd.out cd hoge world
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] cd hoge world"
cd hoge world
echo $?
cd $WORKDIR
echo

# cd -a
printf "${CYAN}%s${RESET}\n" "pwd:
${WORKDIR}"
printf "${YELLOW}%s${RESET}\n" "[mini] cd -a"
./cd.out cd -a
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] cd -a"
cd -a
echo $?
cd $WORKDIR
echo

# cd ./-a (mkdir ./-a)
printf "${CYAN}%s${RESET}\n" "pwd:
${WORKDIR}"
printf "${YELLOW}%s${RESET}\n" "mkdir ./-a"
mkdir ./-a
printf "${YELLOW}%s${RESET}\n" "[mini] cd ./-a"
./cd.out cd ./-a
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] cd ./-a"
cd ./-a
echo $?
pwd
printf "PWD: ${PWD}\n"
printf "OLDPWD: ${OLDPWD}\n"
cd $WORKDIR
rm -rf ./-a
echo

# cd -a cdtest
printf "${CYAN}%s${RESET}\n" "pwd:
${WORKDIR}"
printf "${YELLOW}%s${RESET}\n" "mkdir cdtest"
mkdir cdtest
printf "${YELLOW}%s${RESET}\n" "[mini] cd -a cdtest"
./cd.out cd -a cdtest
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] cd -a cdtest"
cd -a cdtest
echo $?
cd $WORKDIR
rm -rf cdtest
echo

# cd --version
printf "${CYAN}%s${RESET}\n" "pwd:
${WORKDIR}"
printf "${YELLOW}%s${RESET}\n" "[mini] cd --version"
./cd.out cd --version
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] cd --version"
cd --version
echo $?
cd $WORKDIR
echo

# cd --
echo "※minishellではパスを引数に取らない場合invalid"
printf "${CYAN}%s${RESET}\n" "pwd:
${WORKDIR}"
printf "${YELLOW}%s${RESET}\n" "[mini] cd --"
./cd.out cd --
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] cd --"
cd --
echo $?
pwd
cd $WORKDIR
echo
