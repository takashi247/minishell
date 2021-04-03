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

/*
** basic GNL parameters
*/

# define MAX_FD 256
# define BUFFER_SIZE 1024
# define GNL_SUCCESS 1
# define GNL_ERROR -1
# define GNL_EOF 0

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

int		get_next_line(int fd, char **line);
void	ft_free_str(char **str);
int		ft_make_token(t_list **tokens, char *line);

#endif