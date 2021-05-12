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

/*
** macro
*/

# define FREE(p) ((p) ? free(p) : (p), (p) = NULL)

typedef enum e_status
{
	FAILED,
	ENV_DELETED,
	TOKEN_DELETED,
	REDIRECT_DELETED,
	COMPLETED
}	t_status;

/*
** a strucutre to store commands
** need to add member variables to store redirection info
*/

typedef struct			s_command
{
	t_list				*args;
	char				*op;
	t_list				*redirects;
	pid_t				pid;
	struct s_command	*next;
	t_bool				expanded;
}						t_command;


/* global variables */

pid_t	g_latest_pid;

/* function declarations */

int			get_next_line(int fd, char **line);
void		ft_free_str(char **str);
int			ft_make_token(t_list **tokens, char *line, t_bool(*f)(char*, int, int*));
t_bool		ft_is_delimiter_or_quote(char *l, int i, int *fl);
t_bool		ft_is_delimiter(char c);
void		ft_put_fderror(int fd_from);

/* expand_env.c */
int			ft_expand_env_var(t_command *c);
t_bool		ft_remove_char(char **s, int i);
t_bool		ft_is_quote(char *s, int i);

/* utils_tnishina.c */
char		**ft_convert_list(t_list *l);
void		ft_clear_argv(char ***argv);
int			ft_isover_intrange(char *s);
void		ft_exit_n_free_g_vars(int exit_status);

/* handle_signal.c */
void		ft_sig_prior(void);
void		ft_sig_post(void);

/* set_redirection.c */
t_bool		ft_set_redirection(t_list *rd, int std_fds[3]);
void		ft_save_fds(int std_fds[3]);
void		ft_restore_fds(int std_fds[3]);

/* add_space.c */
int			ft_add_space(char **l);

/* make_command.c */
t_bool		ft_is_redirect(char *arg);
int			ft_make_command(t_command **commands, t_list *tokens);
void		ft_clear_commands(t_command **c);

/* extract_redirect.c */
void		ft_extract_redirect(t_command *c);

/* remove_escape.c */
int			ft_remove_escape(t_list *lst);

#endif
