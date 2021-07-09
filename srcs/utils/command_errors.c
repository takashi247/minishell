#include "minishell.h"

void
	ft_do_command_err(char *c)
{
	if (g_ms.status == STATUS_SUCCESS)
	{
		ft_put_cmderror(c, COMMAND_NOT_FOUND_ERR_MSG);
		g_ms.status = STATUS_COMMAND_NOT_FOUND;
	}
	else
		ft_put_cmderror(g_ms.err_arg, g_ms.err_msg);
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
