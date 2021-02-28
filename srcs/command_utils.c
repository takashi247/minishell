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
	ft_put_cmdmsg_fd(char *cmd_name, char *msg, int fd)
{
	ft_putstr_fd(cmd_name, fd);
	ft_putstr_fd(": ", fd);
	ft_putendl_fd(msg, fd);
}

void
	ft_put_cmdmsg_fd_with_arg(char *cmd_name, char *msg, char *arg, int fd)
{
	ft_putstr_fd(cmd_name, fd);
	ft_putstr_fd(": ", fd);
	ft_putstr_fd(msg, fd);
	ft_putstr_fd(": ", fd);
	ft_putendl_fd(arg, fd);
}
