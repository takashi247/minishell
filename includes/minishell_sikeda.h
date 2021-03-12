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
# define CMD_OPTION_ERR "invalid option"
# define CMD_CD_HELP "cd [dir]"
# define CMD_PWD_HELP "pwd"

# define FREE(p) ((p) ? free(p) : (p), (p) = NULL)

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

enum	e_cmd_signal
{
	KEEP_RUNNING,
	STOP
};

char	*g_pwd;

/*
** env_utils.c
*/
char	*ft_getenv(const char *name);
/*
** command_utils.c
*/
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_get_cmd_option(char *option, const char *arg);
void	ft_put_cmderror(char *cmd_name, char *msg);
void	ft_put_cmderror_with_arg(char *cmd_name, char *msg, char *arg);
void	ft_put_cmderror_with_help(char *cmd_name, char *help);
/*
** cd.c
*/
int		ft_cd(char **args);
/*
** pwd.c
*/
int		ft_init_pwd();
int		ft_pwd(char **args);

#endif
