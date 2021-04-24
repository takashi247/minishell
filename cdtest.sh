#!/bin/bash

cd libft
make bonus
cd ..
gcc -g -Wall -Wextra -Werror -I./includes -I./libft -I./test \
    test/test_builtin.c test/test_init.c test/test_exec.c test/test_launch.c \
    srcs/echo.c srcs/cd.c srcs/pwd.c srcs/exit.c srcs/env.c srcs/unset.c \
    srcs/export.c srcs/export_print.c srcs/export_setenv.c \
    srcs/init_env.c srcs/env_utils.c srcs/env_utils2.c srcs/env_sort.c srcs/env_copy.c \
    srcs/utils/utils.c srcs/utils/minishell_errors.c srcs/utils/command_utils.c srcs/utils/command_errors.c \
    -Llibft -lft -D CDTEST -o builtin.out #-D LEAKS

YELLOW=$(printf '\033[33m')
CYAN=$(printf '\033[36m')
RESET=$(printf '\033[0m')

WORKDIR=`pwd`
echo ""

# 引数なし
printf "${CYAN}%s${RESET}\n" "pwd:
${WORKDIR}"
printf "${YELLOW}%s${RESET}\n" "[mini] cd"
./builtin.out cd
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] cd"
cd
echo $?
pwd
printf "PWD: ${PWD}\n"
printf "OLDPWD: ${OLDPWD}\n"
cd $WORKDIR
echo

# 引数特殊 ~ (シェルスクリプトによりminishellのテストも ~ が変数展開されている)
printf "${CYAN}%s${RESET}\n" "pwd:
${WORKDIR}"
printf "${YELLOW}%s${RESET}\n" "[mini] cd ~"
./builtin.out cd ~
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
./builtin.out cd "~"
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
./builtin.out cd ""
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
./builtin.out cd ''
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
./builtin.out cd $HOME
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
./builtin.out cd hoge
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
./builtin.out cd cdtest
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
./builtin.out cd "cdtest"
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
./builtin.out cd "cdtest "
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
./builtin.out cd cdtest hoge
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
./builtin.out cd hoge world
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
./builtin.out cd -a
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
./builtin.out cd ./-a
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
./builtin.out cd -a cdtest
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
./builtin.out cd --version
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] cd --version"
cd --version
echo $?
cd $WORKDIR
echo

# cd --
printf "${CYAN}%s${RESET}\n" "pwd:
${WORKDIR}"
printf "${YELLOW}%s${RESET}\n" "[mini] cd --"
./builtin.out cd --
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] cd --"
cd --
echo $?
pwd
printf "PWD: ${PWD}\n"
printf "OLDPWD: ${OLDPWD}\n"
cd $WORKDIR
echo

# unset HOME; cd;
HOMEDIR=$HOME
printf "${CYAN}%s${RESET}\n" "pwd:
${WORKDIR}"
printf "${CYAN}%s${RESET}\n" "unset HOME"
unset HOME
printf "${YELLOW}%s${RESET}\n" "[mini] cd"
./builtin.out cd
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] cd"
cd
echo $?
cd $WORKDIR
export HOME=$HOMEDIR
echo

# unset HOME; export HOME; cd;
HOMEDIR=$HOME
printf "${CYAN}%s${RESET}\n" "pwd:
${WORKDIR}"
printf "${CYAN}%s${RESET}\n" "unset HOME"
unset HOME
printf "${CYAN}%s${RESET}\n" "export HOME"
export HOME
printf "${YELLOW}%s${RESET}\n" "[mini] cd"
./builtin.out cd
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] cd"
cd
echo $?
cd $WORKDIR
export HOME=$HOMEDIR
echo

# unset HOME; export HOME=..; cd;
HOMEDIR=$HOME
printf "${CYAN}%s${RESET}\n" "pwd:
${WORKDIR}"
printf "${CYAN}%s${RESET}\n" "unset HOME"
unset HOME
printf "${CYAN}%s${RESET}\n" "export HOME=.."
export HOME=..
printf "${YELLOW}%s${RESET}\n" "[mini] cd"
./builtin.out cd
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] cd"
cd
echo $?
pwd
printf "PWD: ${PWD}\n"
printf "OLDPWD: ${OLDPWD}\n"
cd $WORKDIR
export HOME=$HOMEDIR
echo

# mkdir cdtest; cd cdtest ; rmdir ../cdtest ; cd "" ;
printf "${CYAN}%s${RESET}\n" "pwd:
${WORKDIR}"
printf "${YELLOW}%s${RESET}\n" "[mini] mkdir cdtest; cd cdtest ; rmdir ../cdtest ; cd \"\" ; pwd"
${WORKDIR}/builtin.out cd_nodir
echo $?
cd $WORKDIR
printf "${YELLOW}%s${RESET}\n" "[mini] mkdir cdtest; cd cdtest ; rmdir ../cdtest ; cd \"\" ; pwd"
#終了ステータスを取るためのコマンド、出力を消して実行
mkdir cdtest ; cd cdtest ; rmdir ../cdtest ; cd "" 2> /dev/null ; pwd &> /dev/null
echo $?
cd $WORKDIR
#画面表示用のコマンド
mkdir cdtest ; cd cdtest ; rmdir ../cdtest ; cd "" ; pwd
printf "PWD: ${PWD}\n"
printf "OLDPWD: ${OLDPWD}\n"
cd $WORKDIR
echo
