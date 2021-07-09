#include "minishell.h"

void
	ft_put_cderror_no_current(const int errornum)
{
	int	fd;

	fd = STDERR_FILENO;
	ft_putstr_fd("cd: error retrieving current directory: getcwd: ", fd);
	ft_putstr_fd("cannot access parent directories: ", fd);
	ft_putstr_fd(strerror(errornum), fd);
	ft_putchar_fd('\n', fd);
}
