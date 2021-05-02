NAME		:= minishell

UTILDIR		:= ./srcs/utils/
TERMDIR		:= ./srcs/termcaps/

SRCS		:= srcs/init_minishell.c \
				srcs/cd.c srcs/cd_error.c srcs/cd_path_utils.c srcs/cd_fullpath.c \
				srcs/echo.c srcs/pwd.c srcs/exit.c \
				srcs/env.c srcs/unset.c \
				srcs/export.c srcs/export_print.c srcs/export_setenv.c \
				srcs/init_env.c srcs/env_utils.c srcs/env_utils2.c \
				srcs/env_sort.c srcs/env_copy.c \
				srcs/get_next_line.c srcs/make_token.c srcs/make_command.c srcs/expand_env.c \
				srcs/handle_signal.c srcs/set_redirection.c \
				$(UTILDIR)command_utils.c $(UTILDIR)command_errors.c $(UTILDIR)minishell_errors.c \
				$(UTILDIR)tlist_utils.c $(UTILDIR)split_utils.c $(UTILDIR)utils_tnishina.c $(UTILDIR)utils.c
SRCS_PRODUCTION	:= $(SRCS)
SRCS_PRODUCTION	+= srcs/minishell.c
OBJS_PRODUCTION	:= $(SRCS_PRODUCTION:.c=.o)

SRCS_BUILTINTEST	:= $(SRCS)
SRCS_BUILTINTEST	+= test/test_builtin.c test/test_init.c test/test_exec.c test/test_launch.c test/test_cd.c

SRCS_TERMTEST	:= $(SRCS)
SRCS_TERMTEST	+= $(TERMDIR)edit_term.c $(TERMDIR)init_term.c $(TERMDIR)term_utils.c srcs/minishell_term.c

INCLUDE		:= -I./includes/ -I./libft/ -I./test/

LIBDIR		:= ./libft
LIBPATH		:= $(LIBDIR)/libft.a
LFLAGS		:= -L${LIBDIR} -lft -lcurses

CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror
# DEBUG		:= -g -fsanitize=address
DEBUG		:=

RM			:= rm -f
C_GREEN		:= "\x1b[32m"

.c.o:
			$(CC) $(CFLAGS) $(DEBUG) $(INCLUDE) -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJS_PRODUCTION) $(LIBPATH)
			$(CC) $(CFLAGS) $(OBJS_PRODUCTION) $(DEBUG) $(LFLAGS) -o $(NAME)
			@echo $(C_GREEN)"=== Make Done ==="

btest:		$(LIBPATH)
			$(CC) $(CFLAGS) $(SRCS_BUILTINTEST) $(DEBUG) $(INCLUDE) $(LFLAGS) -D TEST -o builtin.out
			@echo $(C_GREEN)"=== Make Done ==="

bltest:		$(LIBPATH)
			$(CC) $(CFLAGS) $(SRCS_BUILTINTEST) $(DEBUG) $(INCLUDE) $(LFLAGS) -D CDTEST -D LEAKS -o builtin.out
			@echo $(C_GREEN)"=== Make Done ==="

cdtest:		$(LIBPATH)
			$(CC) $(CFLAGS) $(SRCS_BUILTINTEST) $(DEBUG) $(INCLUDE) $(LFLAGS) -D CDTEST -o builtin.out
			@echo $(C_GREEN)"=== Make Done ==="

cdltest:	$(LIBPATH)
			$(CC) $(CFLAGS) $(SRCS_BUILTINTEST) $(DEBUG) $(INCLUDE) $(LFLAGS) -D CDTEST -D LEAKS -o builtin.out
			@echo $(C_GREEN)"=== Make Done ==="

termtest:	$(LIBPATH)
			$(CC) $(CFLAGS) $(SRCS_TERMTEST) $(DEBUG) $(INCLUDE) $(LFLAGS) -D TEST -o term.out
			@echo $(C_GREEN)"=== Make Done ==="

$(LIBPATH):
			$(MAKE) -C $(LIBDIR)

clean:
			$(RM) $(OBJS_PRODUCTION)
			$(MAKE) clean -C $(LIBDIR)

fclean:		clean
			$(RM) $(NAME)
			$(MAKE) fclean -C $(LIBDIR)

re:			fclean $(NAME)

.PHONY:		all clean fclean re btest bltest cdtest cdltest termtest
