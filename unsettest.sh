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
    -Llibft -lft -D UNSETTEST -o builtin.out #-D LEAKS

YELLOW=$(printf '\033[33m')
CYAN=$(printf '\033[36m')
RESET=$(printf '\033[0m')

printf "${YELLOW}%s${RESET}\n" "[mini] unset"
./builtin.out unset
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] unset"
echo "unset" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] unset --"
./builtin.out unset --
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] unset --"
echo "unset --" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] unset -a"
./builtin.out unset -a
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] unset -a"
echo "unset -a" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] unset \"\""
./builtin.out unset ""
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] unset \"\""
echo "unset \"\"" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] unset -"
./builtin.out unset -
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] unset -"
echo "unset -" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] unset ---"
./builtin.out unset ---
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] unset ---"
echo "unset ---" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] unset -- -a"
./builtin.out unset -- -a
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] unset -- -a"
echo "unset -- -a" | bash
echo $?
echo

printf "${CYAN}%s${RESET}\n" "export UNSETTEST=0123"
export UNSETTEST=0123
printf "${YELLOW}%s${RESET}\n" "[mini] unset UNSETTEST"
./builtin.out unset UNSETTEST
echo $?
printf "${CYAN}%s${RESET}\n" "export UNSETTEST=0123"
export UNSETTEST=0123
printf "${YELLOW}%s${RESET}\n" "[bash] unset UNSETTEST"
echo "unset UNSETTEST" | bash
echo $?
echo

printf "${CYAN}%s${RESET}\n" "export UNSETTEST2=0123"
export UNSETTEST2=0123
printf "${YELLOW}%s${RESET}\n" "[mini] unset UNSETTEST2"
./builtin.out unset UNSETTEST2
echo $?
printf "${CYAN}%s${RESET}\n" "export UNSETTEST2=0123"
export UNSETTEST2=0123
printf "${YELLOW}%s${RESET}\n" "[bash] unset UNSETTEST2"
echo "unset UNSETTEST2" | bash
echo $?
echo

printf "${CYAN}%s${RESET}\n" "export 2UNSETTEST=0123"
export 2UNSETTEST=0123
printf "${YELLOW}%s${RESET}\n" "[mini] unset 2UNSETTEST"
./builtin.out unset 2UNSETTEST
echo $?
printf "${CYAN}%s${RESET}\n" "export 2UNSETTEST=0123"
export 2UNSETTEST=0123
printf "${YELLOW}%s${RESET}\n" "[bash] unset 2UNSETTEST"
echo "unset 2UNSETTEST" | bash
echo $?
echo

printf "${CYAN}%s${RESET}\n" "export UNSETTEST=0123 UNSETTEST2=abc"
export UNSETTEST=0123 UNSETTEST2=abc
printf "${YELLOW}%s${RESET}\n" "[mini] unset UNSETTEST UNSETTEST2"
./builtin.out unset UNSETTEST UNSETTEST2
echo $?
printf "${CYAN}%s${RESET}\n" "export UNSETTEST=0123 UNSETTEST2=abc"
export UNSETTEST=0123 UNSETTEST2=abc
printf "${YELLOW}%s${RESET}\n" "[bash] unset UNSETTEST UNSETTEST2"
echo "unset UNSETTEST UNSETTEST2" | bash
echo $?
echo

printf "${CYAN}%s${RESET}\n" "export UNSETTEST=0123 UNSETTEST2=abc"
export UNSETTEST=0123 UNSETTEST2=abc
printf "${YELLOW}%s${RESET}\n" "[mini] unset -- UNSETTEST UNSETTEST2"
./builtin.out unset -- UNSETTEST UNSETTEST2
echo $?
printf "${CYAN}%s${RESET}\n" "export UNSETTEST=0123 UNSETTEST2=abc"
export UNSETTEST=0123 UNSETTEST2=abc
printf "${YELLOW}%s${RESET}\n" "[bash] unset -- UNSETTEST UNSETTEST2"
echo "unset -- UNSETTEST UNSETTEST2" | bash
echo $?
echo

printf "${CYAN}%s${RESET}\n" "export UNSETTEST=0123"
export UNSETTEST=0123
printf "${YELLOW}%s${RESET}\n" "[mini] unset UNSETTEST 2UNSETTEST"
./builtin.out unset UNSETTEST 2UNSETTEST
echo $?
printf "${CYAN}%s${RESET}\n" "export UNSETTEST=0123"
export UNSETTEST=0123
printf "${YELLOW}%s${RESET}\n" "[bash] unset UNSETTEST 2UNSETTEST"
echo "unset UNSETTEST 2UNSETTEST" | bash
echo $?
echo

printf "${CYAN}%s${RESET}\n" "export UNSETTEST=0123"
export UNSETTEST=0123
printf "${YELLOW}%s${RESET}\n" "[mini] unset -a UNSETTEST 2UNSETTEST"
./builtin.out unset -a UNSETTEST 2UNSETTEST
echo $?
printf "${CYAN}%s${RESET}\n" "export UNSETTEST=0123"
export UNSETTEST=0123
printf "${YELLOW}%s${RESET}\n" "[bash] unset -a UNSETTEST 2UNSETTEST"
echo "unset -a UNSETTEST 2UNSETTEST" | bash
echo $?
echo

printf "${CYAN}%s${RESET}\n" "export _A=0123"
export _A=0123
printf "${YELLOW}%s${RESET}\n" "[mini] unset _A"
./builtin.out unset _A
echo $?
printf "${CYAN}%s${RESET}\n" "export _A=0123"
export _A=0123
printf "${YELLOW}%s${RESET}\n" "[bash] unset _A"
echo "unset _A" | bash
echo $?
echo

printf "${CYAN}%s${RESET}\n" "export _A=0123 A_B=ab"
export _A=0123 A_B=ab
printf "${YELLOW}%s${RESET}\n" "[mini] unset _A A_B"
./builtin.out unset _A A_B
echo $?
printf "${CYAN}%s${RESET}\n" "export _A=0123 A_B=ab"
export _A=0123 A_B=ab
printf "${YELLOW}%s${RESET}\n" "[bash] unset _A A_B"
echo "unset _A A_B" | bash
echo $?
echo
