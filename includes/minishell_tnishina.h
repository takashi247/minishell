#ifndef MINISHELL_TNISHINA_H
# define MINISHELL_TNISHINA_H

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

/*
** required header files
*/

# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>
# include <unistd.h>
# include <string.h>

int		get_next_line(int fd, char **line);
void	ft_free_str(char **str);

#endif