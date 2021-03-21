#!/bin/bash

cd libft
make bonus
cd ..
gcc -g -Wall -Wextra -Werror -I./includes -I./libft srcs/cd.c srcs/pwd.c srcs/exit.c srcs/env.c srcs/command_utils.c srcs/env_utils.c -Llibft -lft -D ENVTEST -o env.out

YELLOW=$(printf '\033[33m')
RESET=$(printf '\033[0m')

printf "${YELLOW}%s${RESET}\n" "[mini] env"
./env.out env > mini_env
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
./env.out env -- > mini_env
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

printf "${YELLOW}%s${RESET}\n" "[mini] env -a"
./env.out env -a
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] env -a"
echo "env -a" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] env - - -a"
./env.out env - - -a
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] env - - -a"
echo "env - - -a" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] env --envtestdir"
./env.out env --envtestdir
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] env --envtestdir"
echo "env --envtestdir" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] env envtestdir"
./env.out env envtestdir
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] env envtestdir"
echo "env envtestdir" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] env -"
./env.out env -
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] env -"
echo "env -" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] env - -"
./env.out env - -
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] env - -"
echo "env - -" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] env - - - ----"
./env.out env - - - ----
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] env - - - ----"
echo "env - - - ----" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] env - - - --"
./env.out env - - - --
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] env - - - --"
echo "env - - - --" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] env - - - -- -"
./env.out env - - - -- -
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] env - - - -- -"
echo "env - - - -- -" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] env - - - -- -a"
./env.out env - - - -- -a
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] env - - - -- -a"
echo "env - - - -- -a" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] env - - - --- -a"
./env.out env - - - --- -a
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] env - - - --- -a"
echo "env - - - --- -a" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] env -- -"
./env.out env -- -
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] env -- -"
echo "env -- -" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] env -- --"
./env.out env -- --
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] env -- --"
echo "env -- --" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] env --- -"
./env.out env --- -
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] env --- -"
echo "env --- -" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] env - envtestdir"
./env.out env - envtestdir
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] env - envtestdir"
echo "env - envtestdir" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] env -- envtestdir"
./env.out env -- envtestdir
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] env -- envtestdir"
echo "env -- envtestdir" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] env --- envtestdir"
./env.out env --- envtestdir
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] env --- envtestdir"
echo "env --- envtestdir" | bash
echo $?
echo
