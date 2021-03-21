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
# define STATUS_SUCCESS 0
# define STATUS_GENERAL_ERR 1
# define STATUS_OUT_OF_RANGE_ERR 255
# define CMD_OPTION_ERR "invalid option"
# define CMD_CD_HELP "cd [dir]"
# define CMD_PWD_HELP "pwd"
# define CMD_ENV_HELP "env"

# define SPACE_CHARS " \t\n\v\f\r"

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

uint8_t	g_status;
char	*g_pwd;
t_list	*g_env;

/*
** env_utils.c
*/
char	*ft_getenv(const char *name);
/*
** command_utils.c
*/
int		ft_strcmp(const char *s1, const char *s2);
int		ft_isspace(char c);
int		ft_isnumeric(char *s);
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
int		ft_init_pwd(void);
int		ft_pwd(char **args);
/*
** env.c
*/
int		ft_init_env(void);
int		ft_env(char **args);
/*
** exit.c
*/
int		ft_exit(char **args);

#endif
