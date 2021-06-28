NAME		:= minishell
NAME_LEAKS	:= minishell_leaks
NAME_GNL	:= minishell_gnl.out
NAME_TEST	:= builtin.out

SRCSDIR		:= ./srcs/
BUILTINDIR	:= builtins/
ENVDIR		:= env/
HISTDIR		:= history/
TERMDIR		:= termcaps/
UTILDIR		:= utils/

SRCS		:= add_space.c \
				create_n_add_command.c \
				do_command.c \
				do_nonpath_command.c \
				do_path_command.c \
				execute_builtin.c \
				execute_pipeline.c \
				execute_redirection.c \
				expand_env.c \
				extract_redirect.c \
				find_n_replace_env.c \
				get_next_line.c \
				get_pathenv.c \
				handle_signal.c \
				handle_signal_w_gnl.c \
				heredocument.c \
				init_minishell.c \
				is_delimiter_or_quote.c \
				make_command.c \
				make_token.c \
				minishell.c \
				ms_get_next_line.c \
				pipe_signal.c \
				reconnect_tokens.c \
				replace_env.c \
				replace_env_token.c \
				replace_q_env.c \
				run_commandline.c \
				run_commands.c \
				set_redirection.c \
				has_env_in_path.c \
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
SRCS		:= $(addprefix $(SRCSDIR), $(SRCS))
OBJS		:= $(SRCS:.c=.o)

SRCS_GNL	:= $(SRCSDIR)minishell_w_gnl.c
OBJS_GNL	:= $(SRCS_GNL:.c=.o)

SRCS_BUILTINTEST	:= test/test_builtin.c test/test_init.c test/test_exec.c test/test_launch.c test/test_cd.c
OBJS_BUILTINTEST	:= $(SRCS_BUILTINTEST:.c=.o)

SRCS_LEAKS	:= $(SRCSDIR)leaks.c
OBJS_LEAKS	:= $(SRCS_LEAKS:.c=.o)

ifdef LEAKS
NAME		:= $(NAME_LEAKS)
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

$(NAME):	$(OBJS) $(LIBPATH)
			$(CC) $(CFLAGS) $(OBJS) $(DEBUG) $(LFLAGS) -o $(NAME)
			@echo $(C_GREEN)"=== Make Done ==="

gnl:		$(LIBPATH)
			$(RM) $(SRCSDIR)minishell.o $(SRCSDIR)init_minishell.o
			$(MAKE) CFLAGS="$(CFLAGS) -D WITH_GNL" SRCS="$(SRCS) $(SRCS_GNL)"
			mv $(NAME) $(NAME_GNL)

btest:		$(LIBPATH)	## Compile for commands testing.
			$(RM) $(SRCSDIR)minishell.o test/test_init.o
			$(MAKE) CFLAGS="$(CFLAGS) -D TEST" SRCS="$(SRCS) $(SRCS_BUILTINTEST)"
			mv $(NAME) $(NAME_TEST)

bltest:		$(LIBPATH)	## Compile for commands testing with `leaks'.
			$(RM) $(SRCSDIR)minishell.o test/test_init.o
			$(MAKE) CFLAGS="$(CFLAGS) -D TEST -D LEAKS" SRCS="$(SRCS) $(SRCS_BUILTINTEST)"
			mv $(NAME) $(NAME_TEST)

cdtest:		$(LIBPATH)	## Compile for cd command testing.
			$(RM) $(SRCSDIR)minishell.o test/test_init.o
			$(MAKE) CFLAGS="$(CFLAGS) -D CDTEST" SRCS="$(SRCS) $(SRCS_BUILTINTEST)"
			mv $(NAME) $(NAME_TEST)

cdltest:	$(LIBPATH)	## Compile for cd command testing with `leaks'.
			$(RM) $(SRCSDIR)minishell.o test/test_init.o
			$(MAKE) CFLAGS="$(CFLAGS) -D CDTEST -D LEAKS" SRCS="$(SRCS) $(SRCS_BUILTINTEST)"
			mv $(NAME) $(NAME_TEST)

leaks:		$(LIBPATH)	## For leak check
			$(MAKE) CFLAGS="$(CFLAGS) -D LEAKS=1" SRCS="$(SRCS) $(SRCS_LEAKS)" LEAKS=TRUE

$(LIBPATH):
			$(MAKE) -C $(LIBDIR)

clean:		## Remove all the temporary generated files.
			$(RM) $(OBJS) $(OBJS_LEAKS) $(OBJS_GNL) $(OBJS_BUILTINTEST)
			$(MAKE) clean -C $(LIBDIR)

fclean:		clean	## `make clean' plus all the binary made with `make all'.
			$(RM) $(NAME) $(NAME_LEAKS) $(NAME_GNL) $(NAME_TEST)
			$(MAKE) fclean -C $(LIBDIR)

re:			fclean $(NAME)	## `make fclean' followed by `make all'.

bonus:		$(NAME)	## For bonus

help:		## Display this help screen.
			@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-15s\033[0m %s\n", $$1, $$2}'

.PHONY:		all clean fclean re help btest bltest cdtest cdltest leaks
