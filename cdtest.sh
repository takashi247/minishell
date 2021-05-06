#!/bin/bash

# USAGE ##################
#
# all test
# ./cdtest.sh
#
# all test with leaks
# ./cdtest.sh leaks
#
# make only
# ./cdtest.sh make
#
##########################

if [ "$1" = "leaks" ]; then
    make cdltest # LEAK TEST
else
    make cdtest
fi

if [ "$1" = "make" ]; then
    exit
fi

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

# cd .
printf "${CYAN}%s${RESET}\n" "pwd:
${WORKDIR}"
printf "${YELLOW}%s${RESET}\n" "[mini] cd ."
./builtin.out cd .
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] cd ."
cd .
echo $?
pwd
printf "PWD: ${PWD}\n"
printf "OLDPWD: ${OLDPWD}\n"
cd $WORKDIR
echo

# cd ..
printf "${CYAN}%s${RESET}\n" "pwd:
${WORKDIR}"
printf "${YELLOW}%s${RESET}\n" "[mini] cd .."
./builtin.out cd ..
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] cd .."
cd ..
echo $?
pwd
printf "PWD: ${PWD}\n"
printf "OLDPWD: ${OLDPWD}\n"
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

# cd CDtest
printf "${CYAN}%s${RESET}\n" "pwd:
${WORKDIR}"
printf "${YELLOW}%s${RESET}\n" "mkdir cdtest"
mkdir cdtest
printf "${YELLOW}%s${RESET}\n" "[mini] cd CDtest"
./builtin.out cd CDtest
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] cd CDtest"
cd CDtest
echo $?
pwd
printf "PWD: ${PWD}\n"
printf "OLDPWD: ${OLDPWD}\n"
cd $WORKDIR
rm -rf cdtest
echo

# cd /..
printf "${CYAN}%s${RESET}\n" "pwd:
${WORKDIR}"
printf "${YELLOW}%s${RESET}\n" "[mini] cd /.."
./builtin.out cd /..
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] cd /.."
cd /..
echo $?
pwd
printf "PWD: ${PWD}\n"
printf "OLDPWD: ${OLDPWD}\n"
cd $WORKDIR
rm -rf cdtest
echo

# cd /./../
printf "${CYAN}%s${RESET}\n" "pwd:
${WORKDIR}"
printf "${YELLOW}%s${RESET}\n" "[mini] cd /./../"
./builtin.out cd /./../
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] cd /./../"
cd /./../
echo $?
pwd
printf "PWD: ${PWD}\n"
printf "OLDPWD: ${OLDPWD}\n"
cd $WORKDIR
rm -rf cdtest
echo

# cd ./CDtest
printf "${CYAN}%s${RESET}\n" "pwd:
${WORKDIR}"
printf "${YELLOW}%s${RESET}\n" "mkdir cdtest"
mkdir cdtest
printf "${YELLOW}%s${RESET}\n" "[mini] cd ./CDtest"
./builtin.out cd ./CDtest
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] cd ./CDtest"
cd ./CDtest
echo $?
pwd
printf "PWD: ${PWD}\n"
printf "OLDPWD: ${OLDPWD}\n"
cd $WORKDIR
rm -rf cdtest
echo

# cd cdtest; cd ../CDTEST
printf "${CYAN}%s${RESET}\n" "pwd:
${WORKDIR}"
printf "${YELLOW}%s${RESET}\n" "mkdir cdtest ; cd cdtest"
mkdir cdtest ; cd cdtest
printf "${YELLOW}%s${RESET}\n" "[mini] cd ../CDTEST"
${WORKDIR}/builtin.out cd ../CDTEST
echo $?
cd $WORKDIR
rm -rf cdtest
printf "${YELLOW}%s${RESET}\n" "mkdir cdtest ; cd cdtest"
mkdir cdtest ; cd cdtest
printf "${YELLOW}%s${RESET}\n" "[bash] cd ../CDTEST"
cd ../CDTEST
echo $?
pwd
printf "PWD: ${PWD}\n"
printf "OLDPWD: ${OLDPWD}\n"
cd $WORKDIR
rm -rf cdtest
echo

# cd test1; cd .../TEST1/TEST2/TEST3/..
printf "${CYAN}%s${RESET}\n" "pwd:
${WORKDIR}"
printf "${YELLOW}%s${RESET}\n" "mkdir -p test1/test2/test3 ; cd test1"
mkdir -p test1/test2/test3 ; cd test1
printf "${YELLOW}%s${RESET}\n" "[mini] cd ../TEST1/TEST2/TEST3/.."
${WORKDIR}/builtin.out cd ../TEST1/TEST2/TEST3/..
echo $?
cd $WORKDIR
rmdir -p test1/test2/test3
printf "${YELLOW}%s${RESET}\n" "mkdir -p test1/test2/test3 ; cd test1"
mkdir -p test1/test2/test3 ; cd test1
printf "${YELLOW}%s${RESET}\n" "[bash] cd ../TEST1/TEST2/TEST3/.."
cd ../TEST1/TEST2/TEST3/..
echo $?
pwd
printf "PWD: ${PWD}\n"
printf "OLDPWD: ${OLDPWD}\n"
cd $WORKDIR
rmdir -p test1/test2/test3
echo

# cd test1; cd ../../../TEST1
printf "${CYAN}%s${RESET}\n" "pwd:
${WORKDIR}"
printf "${YELLOW}%s${RESET}\n" "mkdir -p test1/test2/test3 ; cd test1/test2/test3"
mkdir -p test1/test2/test3 ; cd test1/test2/test3
printf "${YELLOW}%s${RESET}\n" "[mini] cd ../../../TEST1"
${WORKDIR}/builtin.out cd ../../../TEST1
echo $?
cd $WORKDIR
rmdir -p test1/test2/test3
printf "${YELLOW}%s${RESET}\n" "mkdir -p test1/test2/test3 ; cd test1/test2/test3"
mkdir -p test1/test2/test3 ; cd test1/test2/test3
printf "${YELLOW}%s${RESET}\n" "[bash] cd ../../../TEST1"
cd ../../../TEST1
echo $?
pwd
printf "PWD: ${PWD}\n"
printf "OLDPWD: ${OLDPWD}\n"
cd $WORKDIR
rmdir -p test1/test2/test3
echo

# cd / ; cd ""
printf "${CYAN}%s${RESET}\n" "pwd:
${WORKDIR}"
printf "${YELLOW}%s${RESET}\n" "cd /"
cd /
printf "${YELLOW}%s${RESET}\n" "[mini] cd \"\""
${WORKDIR}/builtin.out cd ""
echo $?
cd $WORKDIR
printf "${YELLOW}%s${RESET}\n" "cd /"
cd /
printf "${YELLOW}%s${RESET}\n" "[bash] cd \"\""
cd /
echo $?
pwd
printf "PWD: ${PWD}\n"
printf "OLDPWD: ${OLDPWD}\n"
cd $WORKDIR
echo

# cd / ; cd .
printf "${CYAN}%s${RESET}\n" "pwd:
${WORKDIR}"
printf "${YELLOW}%s${RESET}\n" "cd /"
cd /
printf "${YELLOW}%s${RESET}\n" "[mini] cd ."
${WORKDIR}/builtin.out cd .
echo $?
cd $WORKDIR
printf "${YELLOW}%s${RESET}\n" "cd /"
cd /
printf "${YELLOW}%s${RESET}\n" "[bash] cd ."
cd .
echo $?
pwd
printf "PWD: ${PWD}\n"
printf "OLDPWD: ${OLDPWD}\n"
cd $WORKDIR
echo

# cd / ; cd /
printf "${CYAN}%s${RESET}\n" "pwd:
${WORKDIR}"
printf "${YELLOW}%s${RESET}\n" "cd /"
cd /
printf "${YELLOW}%s${RESET}\n" "[mini] cd /"
${WORKDIR}/builtin.out cd /
echo $?
cd $WORKDIR
printf "${YELLOW}%s${RESET}\n" "cd /"
cd /
printf "${YELLOW}%s${RESET}\n" "[bash] cd /"
cd /
echo $?
pwd
printf "PWD: ${PWD}\n"
printf "OLDPWD: ${OLDPWD}\n"
cd $WORKDIR
echo

# cd / ; cd
printf "${CYAN}%s${RESET}\n" "pwd:
${WORKDIR}"
printf "${YELLOW}%s${RESET}\n" "cd /"
cd /
printf "${YELLOW}%s${RESET}\n" "[mini] cd"
${WORKDIR}/builtin.out cd
echo $?
cd $WORKDIR
printf "${YELLOW}%s${RESET}\n" "cd /"
cd /
printf "${YELLOW}%s${RESET}\n" "[bash] cd"
cd
echo $?
pwd
printf "PWD: ${PWD}\n"
printf "OLDPWD: ${OLDPWD}\n"
cd $WORKDIR
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

# cd cdtest hoge
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

# mkdir cdtest; cd cdtest; rmdir ../cdtest; cd "";
printf "${CYAN}%s${RESET}\n" "pwd:
${WORKDIR}"
printf "${YELLOW}%s${RESET}\n" "[mini] mkdir cdtest; cd cdtest; rmdir ../cdtest; cd \"\"; pwd"
${WORKDIR}/builtin.out cd_nodir ""
echo $?
cd $WORKDIR
printf "${YELLOW}%s${RESET}\n" "[bash] mkdir cdtest; cd cdtest; rmdir ../cdtest; cd \"\"; pwd"
#終了ステータスを取るためのコマンド、出力を消して実行
mkdir cdtest; cd cdtest; rmdir ../cdtest; cd "" 2> /dev/null; pwd &> /dev/null
echo $?
cd $WORKDIR
#画面表示用のコマンド
mkdir cdtest; cd cdtest; rmdir ../cdtest; cd ""; pwd
printf "PWD: ${PWD}\n"
printf "OLDPWD: ${OLDPWD}\n"
cd $WORKDIR
echo

# mkdir cdtest; cd cdtest; rmdir ../cdtest; cd .;
printf "${CYAN}%s${RESET}\n" "pwd:
${WORKDIR}"
printf "${YELLOW}%s${RESET}\n" "[mini] mkdir cdtest; cd cdtest; rmdir ../cdtest; cd .; pwd"
${WORKDIR}/builtin.out cd_nodir .
echo $?
cd $WORKDIR
printf "${YELLOW}%s${RESET}\n" "[bash] mkdir cdtest; cd cdtest; rmdir ../cdtest; cd .; pwd"
#終了ステータスを取るためのコマンド、出力を消して実行
mkdir cdtest; cd cdtest; rmdir ../cdtest; cd . 2> /dev/null; pwd &> /dev/null
echo $?
cd $WORKDIR
#画面表示用のコマンド
mkdir cdtest; cd cdtest; rmdir ../cdtest; cd .; pwd
printf "PWD: ${PWD}\n"
printf "OLDPWD: ${OLDPWD}\n"
cd $WORKDIR
echo

# mkdir cdtest; cd cdtest; rmdir ../cdtest; cd .//.//;
printf "${CYAN}%s${RESET}\n" "pwd:
${WORKDIR}"
printf "${YELLOW}%s${RESET}\n" "[mini] mkdir cdtest; cd cdtest; rmdir ../cdtest; cd .//.//; pwd"
${WORKDIR}/builtin.out cd_nodir .//.//
echo $?
cd $WORKDIR
printf "${YELLOW}%s${RESET}\n" "[bash] mkdir cdtest; cd cdtest; rmdir ../cdtest; cd .//.//; pwd"
#終了ステータスを取るためのコマンド、出力を消して実行
mkdir cdtest; cd cdtest; rmdir ../cdtest; cd .//.// 2> /dev/null; pwd &> /dev/null
echo $?
cd $WORKDIR
#画面表示用のコマンド
mkdir cdtest; cd cdtest; rmdir ../cdtest; cd .//.//; pwd
printf "PWD: ${PWD}\n"
printf "OLDPWD: ${OLDPWD}\n"
cd $WORKDIR
echo

# mkdir cdtest; cd cdtest; rmdir ../cdtest; cd .; cd ..; pwd;
printf "${CYAN}%s${RESET}\n" "pwd:
${WORKDIR}"
printf "${YELLOW}%s${RESET}\n" "[mini] mkdir cdtest; cd cdtest; rmdir ../cdtest; cd .; pwd; cd ..; pwd"
${WORKDIR}/builtin.out cd_nodir2 .
echo $?
cd $WORKDIR
printf "${YELLOW}%s${RESET}\n" "[bash] mkdir cdtest; cd cdtest; rmdir ../cdtest; cd .; pwd; cd ..; pwd"
#終了ステータスを取るためのコマンド、出力を消して実行
mkdir cdtest; cd cdtest; rmdir ../cdtest; cd . 2> /dev/null; cd ..; pwd &> /dev/null
echo $?
cd $WORKDIR
#画面表示用のコマンド
mkdir cdtest; cd cdtest; rmdir ../cdtest; cd .; pwd;
printf "PWD: ${PWD}\n"
printf "OLDPWD: ${OLDPWD}\n"
cd ..; pwd
printf "PWD: ${PWD}\n"
printf "OLDPWD: ${OLDPWD}\n"
cd $WORKDIR
echo

# mkdir cdtest; cd cdtest; rmdir ../cdtest; cd .; cd ..; pwd;
printf "${CYAN}%s${RESET}\n" "pwd:
${WORKDIR}"
printf "${YELLOW}%s${RESET}\n" "[mini] mkdir cdtest; cd cdtest; rmdir ../cdtest; cd ./././.; pwd; cd ..; pwd"
${WORKDIR}/builtin.out cd_nodir2 ./././.
echo $?
cd $WORKDIR
printf "${YELLOW}%s${RESET}\n" "[bash] mkdir cdtest; cd cdtest; rmdir ../cdtest; cd ./././.; pwd; cd ..; pwd"
#終了ステータスを取るためのコマンド、出力を消して実行
mkdir cdtest; cd cdtest; rmdir ../cdtest; cd ./././. 2> /dev/null; cd ..; pwd &> /dev/null
echo $?
cd $WORKDIR
#画面表示用のコマンド
mkdir cdtest; cd cdtest; rmdir ../cdtest; cd ./././.; pwd;
printf "PWD: ${PWD}\n"
printf "OLDPWD: ${OLDPWD}\n"
cd ..; pwd
printf "PWD: ${PWD}\n"
printf "OLDPWD: ${OLDPWD}\n"
cd $WORKDIR
echo
