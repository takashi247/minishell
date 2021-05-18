NAME		:= minishell

SRCSDIR		:= ./srcs/
HISTDIR		:= history/
UTILDIR		:= utils/
TERMDIR		:= termcaps/

SRCS		:= init_minishell.c \
				add_space.c \
				cd.c cd_error.c cd_path_utils.c cd_fullpath.c \
				echo.c pwd.c exit.c \
				env.c unset.c \
				extract_redirect.c \
				export.c export_print.c export_setenv.c \
				init_env.c env_utils.c env_utils2.c \
				env_sort.c env_copy.c \
				get_next_line.c make_token.c make_command.c expand_env.c \
				handle_signal.c set_redirection.c \
				do_nonpath_command.c do_path_command.c get_pathenv.c \
				is_delimiter_or_quote.c create_n_add_command.c \
				execute_redirection.c replace_env.c find_n_replace_env.c \
				replace_env_token.c reconnect_tokens.c replace_q_env.c \
				run_commands.c execute_pipeline.c execute_builtin.c do_command.c \
				run_commandline.c \
				$(HISTDIR)hlist_utils.c \
				$(UTILDIR)command_utils.c $(UTILDIR)command_errors.c $(UTILDIR)minishell_errors.c \
				$(UTILDIR)tlist_utils.c $(UTILDIR)split_utils.c $(UTILDIR)utils_tnishina.c $(UTILDIR)utils.c \
				$(UTILDIR)make_command_utils.c $(UTILDIR)redirection_utils.c $(UTILDIR)expand_utils.c \
				$(TERMDIR)edit_term_history.c $(TERMDIR)edit_term.c $(TERMDIR)get_line.c \
				$(TERMDIR)handle_keys.c $(TERMDIR)init_term.c $(TERMDIR)term_utils.c
SRCS_PRODUCTION	:= $(SRCS)
SRCS_PRODUCTION	+= minishell.c
SRCS_PRODUCTION	:= $(addprefix $(SRCSDIR), $(SRCS_PRODUCTION))
OBJS_PRODUCTION	:= $(SRCS_PRODUCTION:.c=.o)

SRCS_BUILTINTEST	:= $(SRCS)
SRCS_BUILTINTEST	:= $(addprefix $(SRCSDIR), $(SRCS_BUILTINTEST))
SRCS_BUILTINTEST	+= test/test_builtin.c test/test_init.c test/test_exec.c test/test_launch.c test/test_cd.c

SRCS_TERMTEST	:= $(SRCS)
SRCS_TERMTEST	+= minishell_term.c
SRCS_TERMTEST	:= $(addprefix $(SRCSDIR), $(SRCS_TERMTEST))

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

all:		$(NAME)	## `make' this program.

$(NAME):	$(OBJS_PRODUCTION) $(LIBPATH)
			$(CC) $(CFLAGS) $(OBJS_PRODUCTION) $(DEBUG) $(LFLAGS) -o $(NAME)
			@echo $(C_GREEN)"=== Make Done ==="

btest:		$(LIBPATH)	## Compile for commands testing.
			$(CC) $(CFLAGS) $(SRCS_BUILTINTEST) $(DEBUG) $(INCLUDE) $(LFLAGS) -D TEST -o builtin.out
			@echo $(C_GREEN)"=== Make Done ==="

bltest:		$(LIBPATH)	## Compile for commands testing with `leaks'.
			$(CC) $(CFLAGS) $(SRCS_BUILTINTEST) $(DEBUG) $(INCLUDE) $(LFLAGS) -D CDTEST -D LEAKS -o builtin.out
			@echo $(C_GREEN)"=== Make Done ==="

cdtest:		$(LIBPATH)	## Compile for cd command testing.
			$(CC) $(CFLAGS) $(SRCS_BUILTINTEST) $(DEBUG) $(INCLUDE) $(LFLAGS) -D CDTEST -o builtin.out
			@echo $(C_GREEN)"=== Make Done ==="

cdltest:	$(LIBPATH)	## Compile for cd command testing with `leaks'.
			$(CC) $(CFLAGS) $(SRCS_BUILTINTEST) $(DEBUG) $(INCLUDE) $(LFLAGS) -D CDTEST -D LEAKS -o builtin.out
			@echo $(C_GREEN)"=== Make Done ==="

termtest:	$(LIBPATH)	## Compile for testing terminal operations.
			$(CC) $(CFLAGS) $(SRCS_TERMTEST) $(DEBUG) $(INCLUDE) $(LFLAGS) -D TEST -o term.out
			@echo $(C_GREEN)"=== Make Done ==="

$(LIBPATH):
			$(MAKE) -C $(LIBDIR)

clean:		## Remove all the temporary generated files.
			$(RM) $(OBJS_PRODUCTION)
			$(MAKE) clean -C $(LIBDIR)

fclean:		clean	## `make clean' plus all the binary made with `make all'.
			$(RM) $(NAME)
			$(MAKE) fclean -C $(LIBDIR)

re:			fclean $(NAME)	## `make fclean' followed by `make all'.

help:		## Display this help screen.
			@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-15s\033[0m %s\n", $$1, $$2}'

.PHONY:		all clean fclean re help btest bltest cdtest cdltest termtest
