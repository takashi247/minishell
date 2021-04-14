#!/bin/bash

cd libft
make bonus
cd ..
gcc -g -Wall -Wextra -Werror -I./includes -I./libft srcs/echo.c srcs/cd.c srcs/pwd.c srcs/exit.c srcs/env.c srcs/unset.c srcs/export.c srcs/command_utils.c srcs/env_utils.c -Llibft -lft -D ECHOTEST -o echo.out

YELLOW=$(printf '\033[33m')
CYAN=$(printf '\033[36m')
RESET=$(printf '\033[0m')

printf "${YELLOW}%s${RESET}\n" "[mini] echo"
./echo.out echo
echo $?
./echo.out echo > mini_echo
printf "${YELLOW}%s${RESET}\n" "[bash] echo"
echo "echo" | bash
echo $?
echo "echo > bash_echo" | bash
echo "===diff check start==="
diff mini_echo bash_echo
echo "===diff check end==="
rm -rf mini_echo bash_echo
echo

printf "${YELLOW}%s${RESET}\n" "[mini] echo hello"
./echo.out echo hello
echo $?
./echo.out echo hello > mini_echo
printf "${YELLOW}%s${RESET}\n" "[bash] echo hello"
echo "echo hello" | bash
echo $?
echo "echo hello > bash_echo" | bash
echo "===diff check start==="
diff mini_echo bash_echo
echo "===diff check end==="
rm -rf mini_echo bash_echo
echo

printf "${YELLOW}%s${RESET}\n" "[mini] echo hello world"
./echo.out echo hello world
echo $?
./echo.out echo hello world > mini_echo
printf "${YELLOW}%s${RESET}\n" "[bash] echo hello world"
echo "echo hello world" | bash
echo $?
echo "echo hello world > bash_echo" | bash
echo "===diff check start==="
diff mini_echo bash_echo
echo "===diff check end==="
rm -rf mini_echo bash_echo
echo

printf "${YELLOW}%s${RESET}\n" "[mini] echo hello   world"
./echo.out echo hello   world
echo $?
./echo.out echo hello   world > mini_echo
printf "${YELLOW}%s${RESET}\n" "[bash] echo hello   world"
echo "echo hello   world" | bash
echo $?
echo "echo hello   world > bash_echo" | bash
echo "===diff check start==="
diff mini_echo bash_echo
echo "===diff check end==="
rm -rf mini_echo bash_echo
echo

printf "${YELLOW}%s${RESET}\n" "[mini] echo hello   world hoge"
./echo.out echo hello   world hoge
echo $?
./echo.out echo hello   world hoge > mini_echo
printf "${YELLOW}%s${RESET}\n" "[bash] echo hello   world hoge"
echo "echo hello   world hoge" | bash
echo $?
echo "echo hello   world hoge > bash_echo" | bash
echo "===diff check start==="
diff mini_echo bash_echo
echo "===diff check end==="
rm -rf mini_echo bash_echo
echo

printf "${YELLOW}%s${RESET}\n" "[mini] echo \"hello   world\""
./echo.out echo "hello   world"
echo $?
./echo.out echo "hello   world" > mini_echo
printf "${YELLOW}%s${RESET}\n" "[bash] echo \"hello   world\""
echo "echo \"hello   world\"" | bash
echo $?
echo "echo \"hello   world\" > bash_echo" | bash
echo "===diff check start==="
diff mini_echo bash_echo
echo "===diff check end==="
rm -rf mini_echo bash_echo
echo

printf "${YELLOW}%s${RESET}\n" "[mini] echo -n"
./echo.out echo -n
echo $?
./echo.out echo -n > mini_echo
printf "${YELLOW}%s${RESET}\n" "[bash] echo -n"
echo "echo -n" | bash
echo $?
echo "echo -n > bash_echo" | bash
echo "===diff check start==="
diff mini_echo bash_echo
echo "===diff check end==="
rm -rf mini_echo bash_echo
echo

printf "${YELLOW}%s${RESET}\n" "[mini] echo -n hello"
./echo.out echo -n hello
echo $?
./echo.out echo -n hello > mini_echo
printf "${YELLOW}%s${RESET}\n" "[bash] echo -n hello"
echo "echo -n hello" | bash
echo $?
echo "echo -n hello > bash_echo" | bash
echo "===diff check start==="
diff mini_echo bash_echo
echo "===diff check end==="
rm -rf mini_echo bash_echo
echo

printf "${YELLOW}%s${RESET}\n" "[mini] echo -n hello world"
./echo.out echo -n hello world
echo $?
./echo.out echo -n hello world > mini_echo
printf "${YELLOW}%s${RESET}\n" "[bash] echo -n hello world"
echo "echo -n hello world" | bash
echo $?
echo "echo -n hello world > bash_echo" | bash
echo "===diff check start==="
diff mini_echo bash_echo
echo "===diff check end==="
rm -rf mini_echo bash_echo
echo

printf "${YELLOW}%s${RESET}\n" "[mini] echo -n hello   world"
./echo.out echo -n hello   world
echo $?
./echo.out echo -n hello   world > mini_echo
printf "${YELLOW}%s${RESET}\n" "[bash] echo -n hello   world"
echo "echo -n hello   world" | bash
echo $?
echo "echo -n hello   world > bash_echo" | bash
echo "===diff check start==="
diff mini_echo bash_echo
echo "===diff check end==="
rm -rf mini_echo bash_echo
echo

printf "${YELLOW}%s${RESET}\n" "[mini] echo -n \"hello   world\""
./echo.out echo -n "hello   world"
echo $?
./echo.out echo -n "hello   world" > mini_echo
printf "${YELLOW}%s${RESET}\n" "[bash] echo -n \"hello   world\""
echo "echo -n \"hello   world\"" | bash
echo $?
echo "echo -n \"hello   world\" > bash_echo" | bash
echo "===diff check start==="
diff mini_echo bash_echo
echo "===diff check end==="
rm -rf mini_echo bash_echo
echo

printf "${YELLOW}%s${RESET}\n" "[mini] echo -"
./echo.out echo -
echo $?
./echo.out echo - > mini_echo
printf "${YELLOW}%s${RESET}\n" "[bash] echo -"
echo "echo -" | bash
echo $?
echo "echo - > bash_echo" | bash
echo "===diff check start==="
diff mini_echo bash_echo
echo "===diff check end==="
rm -rf mini_echo bash_echo
echo

printf "${YELLOW}%s${RESET}\n" "[mini] echo - hello"
./echo.out echo - hello
echo $?
./echo.out echo - hello > mini_echo
printf "${YELLOW}%s${RESET}\n" "[bash] echo - hello"
echo "echo - hello" | bash
echo $?
echo "echo - hello > bash_echo" | bash
echo "===diff check start==="
diff mini_echo bash_echo
echo "===diff check end==="
rm -rf mini_echo bash_echo
echo

printf "${YELLOW}%s${RESET}\n" "[mini] echo --"
./echo.out echo --
echo $?
./echo.out echo -- > mini_echo
printf "${YELLOW}%s${RESET}\n" "[bash] echo --"
echo "echo --" | bash
echo $?
echo "echo -- > bash_echo" | bash
echo "===diff check start==="
diff mini_echo bash_echo
echo "===diff check end==="
rm -rf mini_echo bash_echo
echo

printf "${YELLOW}%s${RESET}\n" "[mini] echo -- hello"
./echo.out echo -- hello
echo $?
./echo.out echo -- hello > mini_echo
printf "${YELLOW}%s${RESET}\n" "[bash] echo -- hello"
echo "echo -- hello" | bash
echo $?
echo "echo -- hello > bash_echo" | bash
echo "===diff check start==="
diff mini_echo bash_echo
echo "===diff check end==="
rm -rf mini_echo bash_echo
echo
