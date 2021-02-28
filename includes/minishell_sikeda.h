#ifndef MINISHELL_SIKEDA_H
# define MINISHELL_SIKEDA_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
# include "libft.h"

/*
** command_utils.c
*/
int		ft_strcmp(const char *s1, const char *s2);
void	ft_put_cmdmsg_fd(char *cmd_name, char *msg, int fd);
void	ft_put_cmdmsg_fd_with_arg(char *cmd_name, char *msg, char *arg, int fd);

#endif
