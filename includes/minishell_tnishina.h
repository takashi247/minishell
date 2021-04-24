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

/*
** basic parameters for minishell
*/

# define PROMPT "minishell$ "
# define EXIT_PROMPT "exit\n"
# define STATUS_SYNTAX_ERR 258
# define REDIRECT_IN "<"
# define REDIRECT_OUT ">"
# define APPEND_REDIRECT_OUT ">>"
# define FD_MAX 255
# define NEWLINE "newline"

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

# define QUOTATION_ERROR_MSG "multiline commands are not allowed"
# define SYNTAX_ERROR_MSG "syntax error near unexpected token"
# define FD_OOR_MSG "file descriptor out of range"
# define FD_ERROR_MSG "Bad file descriptor"

typedef enum e_status
{
	FAILED,
	ENV_DELETED,
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
	struct s_command	*next;
}						t_command;

int			get_next_line(int fd, char **line);
void		ft_free_str(char **str);
int			ft_make_token(t_list **tokens, char *line, t_bool(*f)(char*, int, int*));
int			ft_make_command(t_command **commands, t_list *tokens);
void		ft_clear_commands(t_command **c);
void		ft_put_syntaxerror_with_token(char *token);
int			ft_expand_env_var(t_command *c);
t_bool		ft_is_delimiter_or_quote(char *l, int i, int *fl);
t_bool		ft_is_delimiter(char c);
void		ft_put_fderror(int fd_from);

#endif