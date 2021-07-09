#ifndef MINISHELL_H
# define MINISHELL_H

/*
** required header files
*/

# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include "libft.h"
# include <sys/stat.h>
# include <signal.h>
# include "t_bool.h"
# include "termcaps.h"

/*
** basic parameters for minishell
*/

# define PRG_NAME "minishell"
# define PROMPT "minishell$ "
# define EXIT_PROMPT "exit\n"
# define STATUS_SUCCESS 0
# define STATUS_GENERAL_ERR 1
# define STATUS_MISUSE_OF_BUILTINS_ERR 2
# define STATUS_CANNOT_EXECUTE 126
# define STATUS_COMMAND_NOT_FOUND 127
# define STATUS_OUT_OF_RANGE_ERR 255
# define STATUS_SYNTAX_ERR 258
# define REDIRECT_IN "<"
# define REDIRECT_OUT ">"
# define APPEND_REDIRECT_OUT ">>"
# define HEREDOC "<<"
# define FD_MAX 255
# define NEWLINE "newline"
# define SPACE_CHARS " \t\n\v\f\r"
# define UTIL_SUCCESS 0
# define UTIL_ERROR -1
# define IS_OVERFLOW -127
# define HEREDOC_PROMPT "> "
# define HEREDOC_PATH "/tmp/sh-thd.minishell"

/* do_command parameters */

# define NO_ERROR -1

/* redirection parameters */

# define NO_FD_SETTING -1
# define GENERAL_ERROR -2
# define OVER_INT_RANGE -3

/*
** basic GNL parameters
*/

# define MAX_FD 256
# define BUFFER_SIZE 1
# define GNL_SUCCESS 1
# define GNL_ERROR -1
# define GNL_EOF 0
# define GNL_HEREDOC_EOF -2
# define GNL_SIGINT -3

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

# define CMD_OPTION_ERR "invalid option"
# define CMD_IDENTIFIER_ERR "not a valid identifier"
# define CMD_CD_HELP "cd [dir]"
# define CMD_PWD_HELP "pwd"
# define CMD_ENV_HELP "env"
# define CMD_EXPORT_HELP "export [name[=value] ...]"
# define CMD_UNSET_HELP "unset [name ...]"

typedef enum e_cmd_signal
{
	KEEP_RUNNING,
	STOP,
	EXIT,
	EXIT_NON_NUMERIC
}	t_cmd_signal;

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

/* structures to manage history */

typedef struct s_history
{
	size_t				len;
	char				*line;
	struct s_history	*prev;
	struct s_history	*next;
}	t_history;

typedef struct s_history_list
{
	t_history	*current;
	t_history	*last;
	char		*input;
	size_t		input_len;
}	t_history_list;

/* global variables */

typedef struct s_minishell
{
	t_terminfo		terminfo;
	struct termios	ms_term;
	struct termios	origin_term;
	t_bool			interrupted;
	char			interrupted_buf[4];
	t_history_list	hist;
	char			*pwd;
	char			*sh_pwd;
	char			*sh_oldpwd;
	int				status;
	t_list			*env;
	pid_t			latest_pid;
	char			*err_arg;
	char			*err_msg;
}	t_minishell;

t_minishell	g_ms;

/* function declarations */

/* builtins/cd/cd.c */
int			ft_cd(char **args);

/* builtins/cd/cd_error.c */
void		ft_put_cderror_no_current(const int errornum);

/* builtins/cd/cd_fullpath.c */
char		*ft_make_full_path(const char *input_path);

/* builtins/cd/cd_path_utils.c */
char		*ft_join_path(const char *path, const char *new);
char		*ft_get_home_path(const char *args);

/* builtins/cd/exec_cd_path.c */
int			ft_exec_cd_path(char **path, char **cd_path);

/* builtins/cd/get_cd_result.c */
int			ft_get_cd_result(char **path, const char *args);

/* builtins/echo.c */
int			ft_echo(char **args);

/* builtins/env.c */
int			ft_env(char **args);

/* builtins/exit.c */
int			ft_exit(char **args);

/* builtins/export.c */
int			ft_export(char **args);
t_bool		ft_validate_name(const char *arg);

/* builtins/export_print.c */
int			ft_print_export(void);

/* builtins/export_setenv.c */
int			ft_export_setenv(
				char **args, const char *name, const t_bool plus_mode);

/* builtins/pwd.c */
int			ft_init_pwd(void);
int			ft_pwd(char **args);

/* builtins/unset.c */
int			ft_unset(char **args);

/* env/env_copy.c */
void		ft_clear_copied_env(t_list **cpy);
t_list		*ft_copy_env(void);

/* env/env_sort.c */
void		ft_envsort(t_list **lst);

/* env/env_utils.c */
char		*ft_getenv(const char *name);
int			ft_setenv(char *str);
int			ft_setenv_sep(const char *name, const char *value);
int			ft_unsetenv(const char *name);

/* env/env_utils2.c */
char		*ft_extract_envname_from_str(const char *str);
char		*ft_extract_envvalue_from_str(const char *str);

/* env/inir_env.c */
int			ft_init_env(void);

/* history/utils.c */
int			ft_add_history(
				t_history_list *hlist, const char *line, const size_t len);
int			ft_next_history(t_history_list *hlist);
int			ft_prev_history(t_history_list *hlist);
void		ft_delone_history(t_history *node);
void		ft_clear_history(t_history **node_ptr);

/* utils/command_errors.c */
void		ft_put_cmderror(char *cmd_name, char *msg);
void		ft_put_cmderror_with_arg(char *cmd_name, char *msg, char *arg);
void		ft_put_cmderror_with_quoted_arg(
				char *cmd_name, char *msg, char *arg);
void		ft_put_cmderror_with_help(char *cmd_name, char *help);
void		ft_do_command_err(char *c);

/* utils/command_utils.c */
char		*ft_get_cmd_option(char *option, const char *arg);

/* utils/expand_utils.c */
t_bool		ft_is_space(char *l, int i, int *fl);
t_bool		ft_remove_char(char **s, int i);
t_bool		ft_is_quote(char *s, int i);
t_bool		ft_is_escapable_in_dquote(char c);
t_bool		ft_is_env_name_end(char c);

/* utils/free_utils.c */
void		ft_clear_argv(char ***argv);
void		ft_free(char **ptr);
int			ft_free_n_return(char **ptr, int return_value);

/* utils/make_command_utils.c */
void		ft_clear_commands(t_command **c);
int			ft_clear_commands_n_tokens(t_command **c, t_list **t1, t_list **t2);
int			ft_clear_with_syntax_error(t_command **c, t_list **t);
t_bool		ft_is_redirect(char *arg);

/* utils/minishell_errors.c */
void		ft_put_error(char *msg);
void		ft_put_syntaxerror_with_token(char *token);
void		ft_put_fderror(int fd_from, t_bool res);

/* utils/minihsell_utils.c */
void		ft_exit_n_free_g_vars(int exit_status);

/* utils/redirection_utils.c */
void		ft_save_fds(t_command *c, int std_fds[3]);
void		ft_restore_fds(t_command *c, int std_fds[3]);
t_bool		ft_check_param_error(int fd_from, char *path, char *redirect_op);
t_bool		ft_is_valid_path(const char *path);
t_bool		ft_validate_path(t_list *rd, char **path, char *pre_exp, int res);

/* utils/split_utils.c */
void		ft_free_split(char ***split);
char		*ft_free_split_and_return_str(
				char ***split, const char *return_value);
int			ft_free_split_and_return_int(char ***split, const int return_value);

/* utils/str_utils.c */
char		*ft_strndup_append_null(const char *s, size_t n);
int			ft_strcmp(const char *s1, const char *s2);

/* utils/tlist_utils.c */
void		ft_lstdelend(t_list **lst, void (*del)(void*));
int			ft_lstnew_and_lstadd_back(t_list **path_list, const char *str);

/* utils/typerage_utils.c */
int			ft_isover_llrange(char *s);
int			ft_isover_intrange(char *s);

/* utils/utils.c */
void		*ft_realloc(void *original, size_t size, size_t original_size);
int			ft_isspace(char c);
int			ft_isnumeric(char *s);
char		**ft_convert_list(t_list *l);

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

/* handle_signal.c */
void		ft_sig_prior(void);
void		ft_sig_post(void);

/* set_rd_params.c */
t_bool		ft_set_rd_params_for_heredoc(
				t_list *rd, int *fd_from, char **op, char **path);
t_bool		ft_set_rd_params(t_list *rd, int *fd_from, char **op, char **path);

/* set_redirection.c */
void		ft_free_n_update_params(t_list **rd, char **op, char **path);
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
void		ft_do_path_command(char **argv, char **command_dir);
void		ft_execute_w_environ(char **argv);

/* do_nonpath_command.c */
void		ft_do_nonpath_command(char **path_env, char ***argv);

/* create_n_add_command.c */
t_command	*ft_create_command(t_list *token_head);
t_bool		ft_is_operator(char c);
void		ft_add_command(t_command **head, t_command *new);
t_command	*ft_get_last_command(t_command *head);

/* heredocument.c */
t_bool		ft_execute_all_heredoc(t_command *command);

/* execute_redirection.c */
t_bool		ft_execute_redirection(int fd, char *op, char *path, int stdfds[3]);

/* replace_env.c */
int			ft_replace_env(t_list **args, int fl[4], int *i, t_bool is_rd);

/* find_n_replace_env.c */
int			ft_expand_env_for_heredoc(t_list **args);
int			ft_expand_quotation(char **s);
int			ft_find_n_replace_env(t_list **args, t_bool is_redirect);

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
int			ft_execute_builtin(t_bool is_pipe, t_command *c);

/* do_command.c */
void		ft_do_command(t_command *c);

/* run_commandline.c */
void		ft_run_commandline(char **av);

/* minishell.c */
t_command	*ft_convert_line(char **line, t_command **commands);
t_bool		ft_is_end_with_escape(char *line);

/* pipe_signal.c */
void		ft_sig_pipe(void);
void		ft_handle_post_pipe_signal(int signal);

/* init_minishell.c */
int			init_minishell(int ac);

/* ms_get_next_line.c */
int			ft_ms_get_next_line(char **line);

/* handle_signal_w_gnl.c */
void		ft_sig_prior_w_gnl(void);

/* has_env_in_path.c */
t_bool		ft_has_env_in_path(char *path);

#endif
