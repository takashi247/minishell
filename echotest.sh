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
    -Llibft -lft -D ECHOTEST -o builtin.out #-D LEAKS

YELLOW=$(printf '\033[33m')
CYAN=$(printf '\033[36m')
RESET=$(printf '\033[0m')

printf "${YELLOW}%s${RESET}\n" "[mini] echo"
./builtin.out echo
echo $?
./builtin.out echo > mini_echo
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
./builtin.out echo hello
echo $?
./builtin.out echo hello > mini_echo
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
./builtin.out echo hello world
echo $?
./builtin.out echo hello world > mini_echo
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
./builtin.out echo hello   world
echo $?
./builtin.out echo hello   world > mini_echo
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
./builtin.out echo hello   world hoge
echo $?
./builtin.out echo hello   world hoge > mini_echo
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
./builtin.out echo "hello   world"
echo $?
./builtin.out echo "hello   world" > mini_echo
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
./builtin.out echo -n
echo $?
./builtin.out echo -n > mini_echo
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
./builtin.out echo -n hello
echo $?
./builtin.out echo -n hello > mini_echo
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
./builtin.out echo -n hello world
echo $?
./builtin.out echo -n hello world > mini_echo
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
./builtin.out echo -n hello   world
echo $?
./builtin.out echo -n hello   world > mini_echo
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
./builtin.out echo -n "hello   world"
echo $?
./builtin.out echo -n "hello   world" > mini_echo
printf "${YELLOW}%s${RESET}\n" "[bash] echo -n \"hello   world\""
echo "echo -n \"hello   world\"" | bash
echo $?
echo "echo -n \"hello   world\" > bash_echo" | bash
echo "===diff check start==="
diff mini_echo bash_echo
echo "===diff check end==="
rm -rf mini_echo bash_echo
echo

printf "${YELLOW}%s${RESET}\n" "[mini] echo -nnn hello"
./builtin.out echo -nnn hello
echo $?
./builtin.out echo -nnn hello > mini_echo
printf "${YELLOW}%s${RESET}\n" "[bash] echo -nnn hello"
echo "echo -nnn hello" | bash
echo $?
echo "echo -nnn hello > bash_echo" | bash
echo "===diff check start==="
diff mini_echo bash_echo
echo "===diff check end==="
rm -rf mini_echo bash_echo
echo

printf "${YELLOW}%s${RESET}\n" "[mini] echo -nNn hello"
./builtin.out echo -nNn hello
echo $?
./builtin.out echo -nNn hello > mini_echo
printf "${YELLOW}%s${RESET}\n" "[bash] echo -nNn hello"
echo "echo -nNn hello" | bash
echo $?
echo "echo -nNn hello > bash_echo" | bash
echo "===diff check start==="
diff mini_echo bash_echo
echo "===diff check end==="
rm -rf mini_echo bash_echo
echo

printf "${YELLOW}%s${RESET}\n" "[mini] echo -n -nnn hello"
./builtin.out echo -n -nnn hello
echo $?
./builtin.out echo -n -nnn hello > mini_echo
printf "${YELLOW}%s${RESET}\n" "[bash] echo -n -nnn hello"
echo "echo -n -nnn hello" | bash
echo $?
echo "echo -n -nnn hello > bash_echo" | bash
echo "===diff check start==="
diff mini_echo bash_echo
echo "===diff check end==="
rm -rf mini_echo bash_echo
echo


printf "${YELLOW}%s${RESET}\n" "[mini] echo -n -N hello"
./builtin.out echo -n -N hello
echo $?
./builtin.out echo -n -N hello > mini_echo
printf "${YELLOW}%s${RESET}\n" "[bash] echo -n -N hello"
echo "echo -n -N hello" | bash
echo $?
echo "echo -n -N hello > bash_echo" | bash
echo "===diff check start==="
diff mini_echo bash_echo
echo "===diff check end==="
rm -rf mini_echo bash_echo
echo

printf "${YELLOW}%s${RESET}\n" "[mini] echo -"
./builtin.out echo -
echo $?
./builtin.out echo - > mini_echo
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
./builtin.out echo - hello
echo $?
./builtin.out echo - hello > mini_echo
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
./builtin.out echo --
echo $?
./builtin.out echo -- > mini_echo
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
./builtin.out echo -- hello
echo $?
./builtin.out echo -- hello > mini_echo
printf "${YELLOW}%s${RESET}\n" "[bash] echo -- hello"
echo "echo -- hello" | bash
echo $?
echo "echo -- hello > bash_echo" | bash
echo "===diff check start==="
diff mini_echo bash_echo
echo "===diff check end==="
rm -rf mini_echo bash_echo
echo
