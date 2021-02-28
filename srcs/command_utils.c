#include "minishell_sikeda.h"

int
	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 || *s2)
	{
		if (*s1 != *s2)
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		s1++;
		s2++;
	}
	return (0);
}

void
	ft_put_cmderror(char *cmd_name, char *msg)
{
	int	fd;

	fd = STDERR_FILENO;
	ft_putstr_fd(PRG_NAME, fd);
	ft_putstr_fd(": ", fd);
	ft_putstr_fd(cmd_name, fd);
	ft_putstr_fd(": ", fd);
	ft_putendl_fd(msg, fd);
}

void
	ft_put_cmderror_with_arg(char *cmd_name, char *msg, char *arg)
{
	int	fd;

	fd = STDERR_FILENO;
	ft_putstr_fd(PRG_NAME, fd);
	ft_putstr_fd(": ", fd);
	ft_putstr_fd(cmd_name, fd);
	ft_putstr_fd(": ", fd);
	ft_putstr_fd(arg, fd);
	ft_putstr_fd(": ", fd);
	ft_putendl_fd(msg, fd);
}
