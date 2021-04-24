#!/bin/bash

cd libft
make bonus
cd ..
gcc -g -Wall -Wextra -Werror -I./includes -I./libft srcs/pwd.c srcs/command_utils.c srcs/env.c srcs/init_env.c srcs/env_utils.c srcs/minishell.c srcs/make_command.c srcs/make_token.c srcs/get_next_line.c srcs/expand_env.c -Llibft -lft -o redirect.out

YELLOW=$(printf '\033[33m')
CYAN=$(printf '\033[36m')
RESET=$(printf '\033[0m')

#printf "\n${CYAN}%s${RESET}\n\n" "***Test starts***"

#printf "${YELLOW}%s${RESET}\n\n" "ls | grep e; echo \$HOME"
#./pipe.out "ls | grep e; echo \$HOME"
#echo

#printf "${YELLOW}%s${RESET}\n\n" "test;test;test;test;"
#./command.out "test;test;test;test;"
#echo

#printf "${YELLOW}%s${RESET}\n\n" "test| test&test>test<;"
#./command.out "test| test&test>test<;"
#echo