#!/bin/bash

cd libft
make bonus
cd ..
gcc -g -Wall -Wextra -Werror -I./includes -I./libft srcs/expand_env.c srcs/pwd.c srcs/env.c srcs/env_utils.c srcs/command_utils.c srcs/make_command.c srcs/make_token.c srcs/get_next_line.c -Llibft -lft -D EXPANDTEST -o expand.out

YELLOW=$(printf '\033[33m')
CYAN=$(printf '\033[36m')
RESET=$(printf '\033[0m')

printf "\n${CYAN}%s${RESET}\n\n" "***Test starts***"

printf "${YELLOW}%s${RESET}\n\n" "export B=\"cho TEST\""
export B="cho TEST"
printf "${YELLOW}%s${RESET}\n\n" "e\$B"
./expand.out "e\$B"
echo

printf "${YELLOW}%s${RESET}\n\n" "export B=\"cho TEST\""
export B="cho TEST"
printf "${YELLOW}%s${RESET}\n\n" "e\"\$B\""
./expand.out "e\"\$B\""
echo

printf "${YELLOW}%s${RESET}\n\n" "export C=\"echo;\""
export C="echo;"
printf "${YELLOW}%s${RESET}\n\n" "\$C"
./expand.out "\$C"
echo

printf "${YELLOW}%s${RESET}\n\n" "export C=\"echo ;\""
export C="echo ;"
printf "${YELLOW}%s${RESET}\n\n" "\$C"
./expand.out "\$C"
echo

printf "${YELLOW}%s${RESET}\n\n" "echo \"This is \"\$HOME\" test\""
./expand.out "echo \"This is \"\$HOME\" test\""
echo