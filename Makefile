NAME		:= minishell

UTILDIR		:= ./srcs/utils/

SRCS		:=
SRCS		+= srcs/cd.c srcs/cd_path_utils.c srcs/cd_fullpath.c \
				srcs/echo.c srcs/pwd.c srcs/exit.c \
				srcs/env.c srcs/unset.c \
				srcs/export.c srcs/export_print.c srcs/export_setenv.c \
				srcs/init_env.c srcs/env_utils.c srcs/env_utils2.c \
				srcs/env_sort.c srcs/env_copy.c \
				$(UTILDIR)command_utils.c $(UTILDIR)command_errors.c $(UTILDIR)minishell_errors.c \
				$(UTILDIR)tlist_utils.c $(UTILDIR)split_utils.c $(UTILDIR)utils.c
OBJS		= $(SRCS:.c=.o)

SRCS_BUITINTEST	:= $(SRCS)
SRCS_BUITINTEST	+= test/test_builtin.c test/test_init.c test/test_exec.c test/test_launch.c
OBJS_BUITINTEST	= $(SRCS_BUITINTEST:.c=.o)

INCLUDE		:= -I./includes/ -I./libft/ -I./test/

LIBDIR		:= ./libft
LIBPATH		:= $(LIBDIR)/libft.a

CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror
# DEBUG		:= -g -fsanitize=address
DEBUG		:=

RM			:= rm -f
C_GREEN		:= "\x1b[32m"

.c.o:
			$(CC) $(CFLAGS) $(DEBUG) $(INCLUDE) -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJS) $(LIBPATH)
			$(CC) $(CFLAGS) $(OBJ) $(DEBUG) $(LIBPATH) -o $(NAME)
			@echo $(C_GREEN)"=== Make Done ==="

btest:		$(LIBPATH)
			$(CC) $(CFLAGS) $(SRCS_BUITINTEST) $(DEBUG) $(INCLUDE) $(LIBPATH) -D TEST -o builtin.out
			@echo $(C_GREEN)"=== Make Done ==="

bltest:		$(LIBPATH)
			$(CC) $(CFLAGS) $(SRCS_BUITINTEST) $(DEBUG) $(INCLUDE) $(LIBPATH) -D CDTEST -D LEAKS -o builtin.out
			@echo $(C_GREEN)"=== Make Done ==="

cdtest:		$(LIBPATH)
			$(CC) $(CFLAGS) $(SRCS_BUITINTEST) $(DEBUG) $(INCLUDE) $(LIBPATH) -D CDTEST -o builtin.out
			@echo $(C_GREEN)"=== Make Done ==="

cdltest:	$(LIBPATH)
			$(CC) $(CFLAGS) $(SRCS_BUITINTEST) $(DEBUG) $(INCLUDE) $(LIBPATH) -D CDTEST -D LEAKS -o builtin.out
			@echo $(C_GREEN)"=== Make Done ==="

$(LIBPATH):
			$(MAKE) bonus -C $(LIBDIR)

clean:
			$(RM) $(OBJS)
			$(RM) $(OBJS_BUITINTEST)
			$(MAKE) clean -C $(LIBDIR)

fclean:		clean
			$(RM) $(NAME)
			$(MAKE) fclean -C $(LIBDIR)

re:			fclean $(NAME)

.PHONY:		all clean fclean re btest bltest cdtest cdltest
