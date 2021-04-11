#!/bin/bash

cd libft
make bonus
cd ..
gcc -g -Wall -Wextra -Werror -I./includes -I./libft srcs/cd.c srcs/pwd.c srcs/exit.c srcs/env.c srcs/unset.c srcs/export.c srcs/init_env.c srcs/command_utils.c srcs/env_utils.c -Llibft -lft -D UNSETTEST -o unset.out

YELLOW=$(printf '\033[33m')
CYAN=$(printf '\033[36m')
RESET=$(printf '\033[0m')

printf "${YELLOW}%s${RESET}\n" "[mini] unset"
./unset.out unset
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] unset"
echo "unset" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] unset --"
./unset.out unset --
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] unset --"
echo "unset --" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] unset -a"
./unset.out unset -a
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] unset -a"
echo "unset -a" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] unset \"\""
./unset.out unset ""
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] unset \"\""
echo "unset \"\"" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] unset -"
./unset.out unset -
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] unset -"
echo "unset -" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] unset ---"
./unset.out unset ---
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] unset ---"
echo "unset ---" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] unset -- -a"
./unset.out unset -- -a
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] unset -- -a"
echo "unset -- -a" | bash
echo $?
echo

printf "${CYAN}%s${RESET}\n" "export UNSETTEST=0123"
export UNSETTEST=0123
printf "${YELLOW}%s${RESET}\n" "[mini] unset UNSETTEST"
./unset.out unset UNSETTEST
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
./unset.out unset UNSETTEST2
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
./unset.out unset 2UNSETTEST
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
./unset.out unset UNSETTEST UNSETTEST2
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
./unset.out unset -- UNSETTEST UNSETTEST2
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
./unset.out unset UNSETTEST 2UNSETTEST
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
./unset.out unset -a UNSETTEST 2UNSETTEST
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
./unset.out unset _A
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
./unset.out unset _A A_B
echo $?
printf "${CYAN}%s${RESET}\n" "export _A=0123 A_B=ab"
export _A=0123 A_B=ab
printf "${YELLOW}%s${RESET}\n" "[bash] unset _A A_B"
echo "unset _A A_B" | bash
echo $?
echo
