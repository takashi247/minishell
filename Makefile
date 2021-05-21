NAME		:= minishell
NAME_LEAKS	:= minishell_leaks

SRCSDIR		:= ./srcs/
BUILTINDIR	:= builtins/
ENVDIR		:= env/
HISTDIR		:= history/
TERMDIR		:= termcaps/
UTILDIR		:= utils/

SRCS		:= init_minishell.c \
				add_space.c \
				extract_redirect.c \
				get_next_line.c make_token.c make_command.c expand_env.c \
				handle_signal.c set_redirection.c \
				do_nonpath_command.c do_path_command.c get_pathenv.c \
				is_delimiter_or_quote.c create_n_add_command.c \
				execute_redirection.c replace_env.c find_n_replace_env.c \
				replace_env_token.c reconnect_tokens.c replace_q_env.c \
				run_commands.c execute_pipeline.c execute_builtin.c do_command.c \
				pipe_signal.c \
				run_commandline.c \
				$(BUILTINDIR)cd/cd.c \
				$(BUILTINDIR)cd/cd_error.c \
				$(BUILTINDIR)cd/cd_fullpath.c \
				$(BUILTINDIR)cd/cd_path_utils.c \
				$(BUILTINDIR)cd/exec_cd_path.c \
				$(BUILTINDIR)cd/get_cd_result.c \
				$(BUILTINDIR)echo.c \
				$(BUILTINDIR)env.c \
				$(BUILTINDIR)exit.c \
				$(BUILTINDIR)export.c \
				$(BUILTINDIR)export_print.c \
				$(BUILTINDIR)export_setenv.c \
				$(BUILTINDIR)pwd.c \
				$(BUILTINDIR)unset.c \
				$(ENVDIR)env_copy.c \
				$(ENVDIR)env_sort.c \
				$(ENVDIR)env_utils.c \
				$(ENVDIR)env_utils2.c \
				$(ENVDIR)init_env.c \
				$(TERMDIR)edit_term.c \
				$(TERMDIR)edit_term_history.c \
				$(TERMDIR)get_line.c \
				$(TERMDIR)handle_keys.c \
				$(TERMDIR)init_term.c \
				$(TERMDIR)term_utils.c \
				$(HISTDIR)hlist_utils.c \
				$(UTILDIR)command_errors.c \
				$(UTILDIR)command_utils.c \
				$(UTILDIR)expand_utils.c \
				$(UTILDIR)free_utils.c \
				$(UTILDIR)make_command_utils.c \
				$(UTILDIR)minishell_errors.c \
				$(UTILDIR)minishell_utils.c \
				$(UTILDIR)redirection_utils.c \
				$(UTILDIR)split_utils.c \
				$(UTILDIR)str_utils.c \
				$(UTILDIR)tlist_utils.c \
				$(UTILDIR)typerange_utils.c \
				$(UTILDIR)utils.c
SRCS_PRODUCTION	:= $(SRCS)
SRCS_PRODUCTION	+= minishell.c
SRCS_PRODUCTION	:= $(addprefix $(SRCSDIR), $(SRCS_PRODUCTION))
OBJS_PRODUCTION	:= $(SRCS_PRODUCTION:.c=.o)

SRCS_BUILTINTEST	:= $(SRCS)
SRCS_BUILTINTEST	+= minishell.c
SRCS_BUILTINTEST	:= $(addprefix $(SRCSDIR), $(SRCS_BUILTINTEST))
SRCS_BUILTINTEST	+= test/test_builtin.c test/test_init.c test/test_exec.c test/test_launch.c test/test_cd.c

SRCS_LEAKS		:= $(SRCSDIR)leaks.c
OBJS_LEAKS		:= $(SRCS_LEAKS:.c=.o)

ifdef LEAKS
NAME			:= $(NAME_LEAKS)
endif

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
			$(CC) $(CFLAGS) $(SRCS_BUILTINTEST) $(DEBUG) $(INCLUDE) $(LFLAGS) -D TEST -D LEAKS -o builtin.out
			@echo $(C_GREEN)"=== Make Done ==="

cdtest:		$(LIBPATH)	## Compile for cd command testing.
			$(CC) $(CFLAGS) $(SRCS_BUILTINTEST) $(DEBUG) $(INCLUDE) $(LFLAGS) -D CDTEST -o builtin.out
			@echo $(C_GREEN)"=== Make Done ==="

cdltest:	$(LIBPATH)	## Compile for cd command testing with `leaks'.
			$(CC) $(CFLAGS) $(SRCS_BUILTINTEST) $(DEBUG) $(INCLUDE) $(LFLAGS) -D CDTEST -D LEAKS -o builtin.out
			@echo $(C_GREEN)"=== Make Done ==="

leaks:		## For leak check
			$(MAKE) CFLAGS="$(CFLAGS) -D LEAKS=1" SRCS_PRODUCTION="$(SRCS_PRODUCTION) $(SRCS_LEAKS)" LEAKS=TRUE

$(LIBPATH):
			$(MAKE) -C $(LIBDIR)

clean:		## Remove all the temporary generated files.
			$(RM) $(OBJS_PRODUCTION) $(OBJS_LEAKS)
			$(MAKE) clean -C $(LIBDIR)

fclean:		clean	## `make clean' plus all the binary made with `make all'.
			$(RM) $(NAME)
			$(MAKE) fclean -C $(LIBDIR)

re:			fclean $(NAME)	## `make fclean' followed by `make all'.

bonus:		$(NAME)	## For bonus

help:		## Display this help screen.
			@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-15s\033[0m %s\n", $$1, $$2}'

.PHONY:		all clean fclean re help btest bltest cdtest cdltest leaks
