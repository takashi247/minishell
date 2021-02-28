#ifndef MINISHELL_SIKEDA_H
# define MINISHELL_SIKEDA_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
# include "libft.h"

# define PRG_NAME "minishell"

/*
** command_utils.c
*/
int		ft_strcmp(const char *s1, const char *s2);
void	ft_put_cmderror(char *cmd_name, char *msg);
void	ft_put_cmderror_with_arg(char *cmd_name, char *msg, char *arg);

#endif
