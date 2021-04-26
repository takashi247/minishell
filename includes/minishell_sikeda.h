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
# define STATUS_MISUSE_OF_BUILTINS_ERR 2
# define STATUS_OUT_OF_RANGE_ERR 255

# define CMD_OPTION_ERR "invalid option"
# define CMD_IDENTIFIER_ERR "not a valid identifier"
# define CMD_CD_HELP "cd [dir]"
# define CMD_PWD_HELP "pwd"
# define CMD_ENV_HELP "env"
# define CMD_EXPORT_HELP "export [name[=value] ...]"
# define CMD_UNSET_HELP "unset [name ...]"

# define UTIL_SUCCESS 0
# define UTIL_ERROR -1

# define SPACE_CHARS " \t\n\v\f\r"

# define FREE(p) ((p) ? free(p) : (p), (p) = NULL)

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef enum e_cmd_signal
{
	KEEP_RUNNING,
	STOP
}	t_cmd_signal;

int		g_status;
char	*g_pwd;
t_list	*g_env;

/* utils/minishell_errors.c */
void	ft_put_error(char *msg);
void	ft_put_syntaxerror_with_token(char *token);

/* utils/utils.c */
int		ft_strcmp(const char *s1, const char *s2);
int		ft_isspace(char c);
int		ft_isnumeric(char *s);
void	ft_free(char **ptr);

/* utils/split_utils.c */
void	ft_free_split(char ***split);
char	*ft_free_split_and_return_str(char ***split, const char *return_value);
int		ft_free_split_and_return_int(char ***split, const int return_value);

/* utils/tlist_utils.c */
void	ft_lstdelend(t_list **lst, void (*del)(void*));
int		ft_lstnew_and_lstadd_back(t_list **path_list, const char *str);

/* utils/command_utils.c */
int		ft_isover_llrange(char *s);
char	*ft_get_cmd_option(char *option, const char *arg);

/* utils/command_errors.c */
void	ft_put_cmderror(char *cmd_name, char *msg);
void	ft_put_cmderror_with_arg(char *cmd_name, char *msg, char *arg);
void	ft_put_cmderror_with_quoted_arg(char *cmd_name, char *msg, char *arg);
void	ft_put_cmderror_with_help(char *cmd_name, char *help);

/* inir_env.c */
int		ft_init_env(void);

/* env_utils.c */
char	*ft_getenv(const char *name);
int		ft_setenv(char *str);
int		ft_setenv_sep(const char *name, const char *value);
int		ft_unsetenv(const char *name);

/* env_sort.c */
void	ft_envsort(t_list **lst);

/* env_copy.c */
void	ft_clear_copied_env(t_list **cpy);
t_list	*ft_copy_env(void);

/* env_utils2.c */
char	*ft_extract_envname_from_str(const char *str);
char	*ft_extract_envvalue_from_str(const char *str);

/* echo.c */
int		ft_echo(char **args);

/* cd.c */
int		ft_cd(char **args);

/* cd_error.c */
void	ft_put_cderror_no_current(const int errornum);

/* cd_path_utils.c */
char	*ft_join_path(const char *path, const char *new);
char	*ft_get_home_path(const char *args);

/* cd_fullpath.c */
char	*ft_make_full_path(const char *input_path);

/* pwd.c */
int		ft_init_pwd(void);
int		ft_pwd(char **args);

/* export.c */
int		ft_export(char **args);

/* export_print.c */
int		ft_print_export(void);

/* export_setenv.c */
int		ft_export_setenv(char **args, const char *name, const t_bool plus_mode);

/* unset.c */
int		ft_unset(char **args);

/* env.c */
int		ft_env(char **args);

/* exit.c */
int		ft_exit(char **args);

#endif
