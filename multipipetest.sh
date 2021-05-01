#!/bin/bash

cd libft
make bonus
cd ..
gcc -g -Wall -Wextra -Werror -I./includes -I./libft \
    srcs/cd.c srcs/cd_error.c srcs/cd_path_utils.c srcs/cd_fullpath.c \
	srcs/echo.c srcs/pwd.c srcs/exit.c \
	srcs/env.c srcs/unset.c \
    srcs/export.c srcs/export_print.c srcs/export_setenv.c \
    srcs/init_env.c srcs/env_utils.c srcs/env_utils2.c \
    srcs/env_sort.c srcs/env_copy.c \
    srcs/utils/utils.c srcs/utils/minishell_errors.c srcs/utils/command_utils.c \
	srcs/utils/command_errors.c srcs/utils/utils_tnishina.c srcs/minishell.c\
	srcs/make_command.c srcs/make_token.c srcs/get_next_line.c srcs/expand_env.c \
    srcs/utils/tlist_utils.c srcs/utils/split_utils.c srcs/set_redirection.c\
    -Llibft -lft -o multipipe.out #-D LEAKS