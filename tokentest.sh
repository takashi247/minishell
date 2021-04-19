#!/bin/bash

cd libft
make bonus
cd ..
gcc -g -Wall -Wextra -Werror -I./includes -I./libft \
    srcs/echo.c srcs/cd.c srcs/pwd.c srcs/exit.c srcs/env.c srcs/unset.c \
    srcs/export.c srcs/export_print.c srcs/export_setenv.c \
    srcs/make_token.c srcs/get_next_line.c \
    srcs/init_env.c srcs/env_utils.c srcs/env_utils2.c srcs/env_sort.c srcs/env_copy.c \
    srcs/utils/utils.c srcs/utils/minishell_errors.c srcs/utils/command_utils.c srcs/utils/command_errors.c \
    -Llibft -lft -D TOKENTEST -o token.out

YELLOW=$(printf '\033[33m')
CYAN=$(printf '\033[36m')
RESET=$(printf '\033[0m')

printf "\n${CYAN}%s${RESET}\n\n" "***Test starts***"

printf "${YELLOW}%s${RESET}\n\n" "\$A | grep e; ls 1> file 2> file2"
./token.out "\$A | grep e; ls 1> file 2> file2"
echo

printf "${YELLOW}%s${RESET}\n\n" "test;test;test;test;"
./token.out "test;test;test;test;"
echo

printf "${YELLOW}%s${RESET}\n\n" "test| test&test>test<;"
./token.out "test| test&test>test<;"
echo

printf "${YELLOW}%s${RESET}\n\n" "echo dir-is-\$PWD"
./token.out "echo dir-is-\$PWD"
echo