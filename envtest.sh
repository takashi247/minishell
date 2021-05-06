#!/bin/bash

# USAGE ##################
#
# all test
# ./envtest.sh
#
# all test with leaks
# ./envtest.sh leaks
#
# make only
# ./envtest.sh make
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

printf "${YELLOW}%s${RESET}\n" "[mini] env"
./builtin.out env > mini_env
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] env"
echo "env > bash_env" | bash
echo $?
# _=で始まる変数は最後に実行したコマンドの引数で、bashとminishellの呼び出し方が異なるので、この値も異なるため除外する
sed -e '/^_=/d' mini_env > mini_env_sed
sed -e '/^_=/d' bash_env > bash_env_sed
# 順番を同じにすることができない（?）ので文字数で比較
cat mini_env_sed | wc > mini_env_wc
cat bash_env_sed | wc > bash_env_wc
echo "===diff check start==="
diff mini_env_wc bash_env_wc
echo "===diff check end==="
rm mini_env mini_env_sed mini_env_wc bash_env bash_env_sed bash_env_wc
echo

printf "${YELLOW}%s${RESET}\n" "[mini] env --"
./builtin.out env -- > mini_env
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] env --"
echo "env > bash_env --" | bash
echo $?
# _=で始まる変数は最後に実行したコマンドの引数で、bashとminishellの呼び出し方が異なるので、この値も異なるため除外する
sed -e '/^_=/d' mini_env > mini_env_sed
sed -e '/^_=/d' bash_env > bash_env_sed
# 順番を同じにすることができない（?）ので文字数で比較
cat mini_env_sed | wc > mini_env_wc
cat bash_env_sed | wc > bash_env_wc
echo "===diff check start==="
diff mini_env_wc bash_env_wc
echo "===diff check end==="
rm mini_env mini_env_sed mini_env_wc bash_env bash_env_sed bash_env_wc
echo

printf "${CYAN}%s${RESET}\n" "export ENVTEST=0123"
export ENVTEST=0123
printf "${YELLOW}%s${RESET}\n" "[mini] env"
./builtin.out env > mini_env
echo $?
printf "${CYAN}%s${RESET}\n" "export ENVTEST=0123"
export ENVTEST=0123
printf "${YELLOW}%s${RESET}\n" "[bash] env"
echo "env > bash_env" | bash
echo $?
# _=で始まる変数は最後に実行したコマンドの引数で、bashとminishellの呼び出し方が異なるので、この値も異なるため除外する
sed -e '/^_=/d' mini_env > mini_env_sed
sed -e '/^_=/d' bash_env > bash_env_sed
# 順番を同じにすることができない（?）ので文字数で比較
cat mini_env_sed | wc > mini_env_wc
cat bash_env_sed | wc > bash_env_wc
echo "===diff check start==="
diff mini_env_wc bash_env_wc
echo "===diff check end==="
rm mini_env mini_env_sed mini_env_wc bash_env bash_env_sed bash_env_wc
echo

printf "${CYAN}%s${RESET}\n" "export ENVTEST"
export ENVTEST
printf "${YELLOW}%s${RESET}\n" "[mini] env"
./builtin.out env > mini_env
echo $?
printf "${CYAN}%s${RESET}\n" "export ENVTEST"
export ENVTEST
printf "${YELLOW}%s${RESET}\n" "[bash] env"
echo "env > bash_env" | bash
echo $?
# _=で始まる変数は最後に実行したコマンドの引数で、bashとminishellの呼び出し方が異なるので、この値も異なるため除外する
sed -e '/^_=/d' mini_env > mini_env_sed
sed -e '/^_=/d' bash_env > bash_env_sed
# 順番を同じにすることができない（?）ので文字数で比較
cat mini_env_sed | wc > mini_env_wc
cat bash_env_sed | wc > bash_env_wc
echo "===diff check start==="
diff mini_env_wc bash_env_wc
echo "===diff check end==="
rm mini_env mini_env_sed mini_env_wc bash_env bash_env_sed bash_env_wc
echo

printf "${CYAN}%s${RESET}\n" "unset PWD"
unset PWD
printf "${YELLOW}%s${RESET}\n" "[mini] env"
./builtin.out env > mini_env
echo $?
printf "${CYAN}%s${RESET}\n" "unset PWD"
unset PWD
printf "${YELLOW}%s${RESET}\n" "[bash] env"
echo "env > bash_env" | bash
echo $?
# _=で始まる変数は最後に実行したコマンドの引数で、bashとminishellの呼び出し方が異なるので、この値も異なるため除外する
sed -e '/^_=/d' mini_env > mini_env_sed
sed -e '/^_=/d' bash_env > bash_env_sed
# 順番を同じにすることができない（?）ので文字数で比較
cat mini_env_sed | wc > mini_env_wc
cat bash_env_sed | wc > bash_env_wc
echo "===diff check start==="
diff mini_env_wc bash_env_wc
echo "===diff check end==="
rm mini_env mini_env_sed mini_env_wc bash_env bash_env_sed bash_env_wc
echo

printf "${CYAN}%s${RESET}\n" "export PWD=hello"
export PWD=hello
printf "${YELLOW}%s${RESET}\n" "[mini] env"
./builtin.out env > mini_env
echo $?
printf "${CYAN}%s${RESET}\n" "export PWD=hello"
export PWD=hello
printf "${YELLOW}%s${RESET}\n" "[bash] env"
echo "env > bash_env" | bash
echo $?
# _=で始まる変数は最後に実行したコマンドの引数で、bashとminishellの呼び出し方が異なるので、この値も異なるため除外する
sed -e '/^_=/d' mini_env > mini_env_sed
sed -e '/^_=/d' bash_env > bash_env_sed
# 順番を同じにすることができない（?）ので文字数で比較
cat mini_env_sed | wc > mini_env_wc
cat bash_env_sed | wc > bash_env_wc
echo "===diff check start==="
diff mini_env_wc bash_env_wc
echo "===diff check end==="
rm mini_env mini_env_sed mini_env_wc bash_env bash_env_sed bash_env_wc
echo

printf "${YELLOW}%s${RESET}\n" "[mini] env -a"
./builtin.out env -a
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] env -a"
echo "env -a" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] env - - -a"
./builtin.out env - - -a
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] env - - -a"
echo "env - - -a" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] env --envtestdir"
./builtin.out env --envtestdir
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] env --envtestdir"
echo "env --envtestdir" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] env envtestdir"
./builtin.out env envtestdir
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] env envtestdir"
echo "env envtestdir" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] env -"
./builtin.out env -
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] env -"
echo "env -" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] env - -"
./builtin.out env - -
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] env - -"
echo "env - -" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] env - - - ----"
./builtin.out env - - - ----
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] env - - - ----"
echo "env - - - ----" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] env - - - --"
./builtin.out env - - - --
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] env - - - --"
echo "env - - - --" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] env - - - -- -"
./builtin.out env - - - -- -
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] env - - - -- -"
echo "env - - - -- -" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] env - - - -- -a"
./builtin.out env - - - -- -a
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] env - - - -- -a"
echo "env - - - -- -a" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] env - - - --- -a"
./builtin.out env - - - --- -a
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] env - - - --- -a"
echo "env - - - --- -a" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] env -- -"
./builtin.out env -- -
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] env -- -"
echo "env -- -" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] env -- --"
./builtin.out env -- --
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] env -- --"
echo "env -- --" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] env --- -"
./builtin.out env --- -
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] env --- -"
echo "env --- -" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] env - envtestdir"
./builtin.out env - envtestdir
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] env - envtestdir"
echo "env - envtestdir" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] env -- envtestdir"
./builtin.out env -- envtestdir
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] env -- envtestdir"
echo "env -- envtestdir" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] env --- envtestdir"
./builtin.out env --- envtestdir
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] env --- envtestdir"
echo "env --- envtestdir" | bash
echo $?
echo
