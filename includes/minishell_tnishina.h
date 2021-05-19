#ifndef MINISHELL_TNISHINA_H
# define MINISHELL_TNISHINA_H

/*
** required header files
*/

# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>
# include <string.h>
# include "libft.h"
# include "minishell_sikeda.h"
# include <sys/stat.h>
# include <signal.h>

/*
** basic parameters for minishell
*/

# define PROMPT "minishell$ "
# define EXIT_PROMPT "exit\n"
# define STATUS_CANNOT_EXECUTE 126
# define STATUS_COMMAND_NOT_FOUND 127
# define STATUS_SYNTAX_ERR 258
# define REDIRECT_IN "<"
# define REDIRECT_OUT ">"
# define APPEND_REDIRECT_OUT ">>"
# define FD_MAX 255
# define NEWLINE "newline"

/* do_command parameters */

# define NO_ERROR -1

/* redirection parameters */

# define NO_FD_SETTING -1
# define TOKEN_ERROR -2
# define OVER_INT_RANGE -3

/*
** basic GNL parameters
*/

# define MAX_FD 256
# define BUFFER_SIZE 1024
# define GNL_SUCCESS 1
# define GNL_ERROR -1
# define GNL_EOF 0

/*
** Error messages
*/

# define MULTILINE_ERROR_MSG "multiline commands are not allowed"
# define SYNTAX_ERROR_MSG "syntax error near unexpected token"
# define FD_OOR_MSG "file descriptor out of range"
# define FD_ERROR_MSG "Bad file descriptor"
# define IS_DIR_ERROR_MSG "is a directory"
# define COMMAND_NOT_FOUND_ERR_MSG "command not found"
# define AMBIGUOUS_REDIRECT_ERR_MSG "ambiguous redirect"
# define IS_NOT_DIR_ERR_MSG "Not a directory"
# define PERMISSION_ERR_MSG "Permission denied"

typedef enum e_status
{
	FAILED,
	CONDITIONS_MET,
	ENV_DELETED,
	TOKEN_DELETED,
	REDIRECT_DELETED,
	COMPLETED
}	t_status;

typedef enum e_cd_status
{
	CD_FAILED,
	CD_SUCCESS,
	CD_PATH_FAILED,
	CD_PATH_SUCCESS,
	MALLOC_ERR
}	t_cd_status;

/*
** a strucutre to store commands
** need to add member variables to store redirection info
*/

typedef struct s_command
{
	t_list				*args;
	char				*op;
	t_list				*redirects;
	pid_t				pid;
	struct s_command	*next;
	t_bool				expanded;
}	t_command;

/* global variables */

pid_t	g_latest_pid;
char	*g_err_arg;
char	*g_err_msg;

/* function declarations */

/* get_next_line.c */
int			get_next_line(int fd, char **line);

/* make_token.c */
int			ft_make_token(
				t_list **tokens, char *line, t_bool(*f)(char*, int, int*));

/* is_delimiter_or_quote.c */
t_bool		ft_is_delimiter_or_quote(char *l, int i, int *fl);
t_bool		ft_is_delimiter(char c);

/* expand_env.c */
int			ft_expand_env_var(t_command *c);

/* utils/utils_tnishina.c */
char		**ft_convert_list(t_list *l);
void		ft_clear_argv(char ***argv);
int			ft_isover_intrange(char *s);
void		ft_exit_n_free_g_vars(int exit_status);

/* handle_signal.c */
void		ft_sig_prior(void);
void		ft_sig_post(void);

/* set_redirection.c */
t_bool		ft_set_redirection(t_list *rd, int std_fds[3]);

/* add_space.c */
void		ft_add_space(char **l);

/* make_command.c */
t_bool		ft_is_redirect(char *arg);
int			ft_make_command(t_command **commands, t_list *tokens);
void		ft_clear_commands(t_command **c);

/* extract_redirect.c */
void		ft_extract_redirect(t_command *c);

/* remove_escape.c */
int			ft_remove_escape(t_list *lst);

/* get_pathenv.c */
char		*ft_get_pathenv(char *s);

/* do_path_command.c */
void		ft_do_path_command(char **argv, char *command_dir);
void		ft_execute_w_environ(char **argv);

/* do_nonpath_command.c */
void		ft_do_nonpath_command(char **path_env, char ***argv);

/* create_n_add_command.c */
t_command	*ft_create_command(t_list *token_head);
t_bool		ft_is_operator(char c);
void		ft_add_command(t_command **head, t_command *new);
t_command	*ft_get_last_command(t_command *head);

/* utils/make_command_utils.c */
void		ft_clear_commands(t_command **c);
int			ft_clear_commands_n_tokens(t_command **c, t_list **t1, t_list **t2);
int			ft_clear_with_syntax_error(t_command **c, t_list **t);
t_bool		ft_is_redirect(char *arg);

/* execute_redirection.c */
t_bool		ft_execute_redirection(int fd, char *op, char *path, int stdfds[3]);

/* utils/redirection_utils.c */
void		ft_save_fds(t_command *c, int std_fds[3]);
void		ft_restore_fds(t_command *c, int std_fds[3]);
t_bool		ft_check_param_error(int fd_from, char *path, char *redirect_op);

/* utils/expand_utils.c */
t_bool		ft_is_space(char *l, int i, int *fl);
t_bool		ft_remove_char(char **s, int i);
t_bool		ft_is_quote(char *s, int i);
t_bool		ft_is_escapable_in_dquote(char c);
t_bool		ft_is_env_name_end(char c);

/* replace_env.c */
int			ft_replace_env(t_list **args, int dq_flag, int eq_flag, int *i);

/* find_n_replace_env.c */
int			ft_find_n_replace_env(t_list **args);

/* replace_env_tokens.c */
int			ft_replace_env_token(t_list **args, int *env_pos, int *i);

/* reconnect_tokens.c */
int			ft_reconnect_tokens(t_list *t, char *new[3], t_list **args, int *i);

/* replace_q_env.c */
void		ft_free_all_chars(char **env, char *tmp[2], char *new[3]);
int			ft_replace_q_env(char **content, int *env_pos, int *i);
t_bool		ft_create_new_strs(char *content, int *env_pos, char *new[3]);

/* run_command.c */
t_bool		ft_is_pipe(t_command *c);
t_bool		ft_is_builtin(t_command *c);
void		ft_run_commands(t_command *commands, int *res);

/* execute_pipeline.c */
t_command	*ft_execute_pipeline(t_command *c);

/* execute_builtin.c */
int			ft_execute_builtin(t_command *c);

/* do_command.c */
void		ft_do_command(t_command *c);

/* run_commandline.c */
void		ft_run_commandline(char **av);

/* minishell.c */
t_command	*ft_convert_line(char **line, t_command **commands);
t_bool		ft_is_end_with_escape(char *line);

/* exec_cd_path.c */
int			ft_exec_cd_path(char **path, char **cd_path);

/* get_cd_result.c */
int			ft_get_cd_result(char **path, const char *args);

#endif
