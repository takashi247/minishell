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

int
	ft_isspace(char c)
{
	return (c == ' ' || (9 <= c && c <= 13));
}

int
	ft_isnumeric(char *s)
{
	if (!s || *s == '\0')
		return (0);
	if (*s == '+' || *s == '-')
		s++;
	if (!ft_isdigit(*s))
		return (0);
	while (*s)
	{
		if (!ft_isdigit(*s++))
			return (0);
	}
	return (1);
}

char
	*ft_get_cmd_option(char *option, const char *arg)
{
	if (!option || !arg)
		return (NULL);
	if (arg[0] == '-' && arg[1] != '\0')
	{
		option[0] = '-';
		option[1] = arg[1];
		option[2] = '\0';
		return (option);
	}
	return (NULL);
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

void
	ft_put_cmderror_with_quoted_arg(char *cmd_name, char *msg, char *arg)
{
	int	fd;

	fd = STDERR_FILENO;
	ft_putstr_fd(PRG_NAME, fd);
	ft_putstr_fd(": ", fd);
	ft_putstr_fd(cmd_name, fd);
	ft_putstr_fd(": `", fd);
	ft_putstr_fd(arg, fd);
	ft_putstr_fd("': ", fd);
	ft_putendl_fd(msg, fd);
}

void
	ft_put_cmderror_with_help(char *cmd_name, char *help)
{
	int	fd;

	fd = STDERR_FILENO;
	ft_putstr_fd(cmd_name, fd);
	ft_putstr_fd(": usage: ", fd);
	ft_putendl_fd(help, fd);
}
