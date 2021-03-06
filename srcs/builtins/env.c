#include "minishell.h"

static void
	put_enverror_with_option(char *option)
{
	int	fd;

	fd = STDERR_FILENO;
	ft_putstr_fd("env: illegal option -- ", fd);
	write(fd, option, 1);
	write(fd, "\n", 1);
	ft_putstr_fd("usage: ", fd);
	ft_putendl_fd(CMD_ENV_HELP, fd);
}

static char
	*check_args(char **args, t_bool *has_path)
{
	char	*option;
	int		i;

	option = NULL;
	while (args[1])
	{
		if (!ft_strcmp(args[1], "--") && args[2])
			*has_path = TRUE;
		else
		{
			i = 0;
			while (args[1][i] == '-')
				i++;
			if (args[1][i] == '\0')
				args++;
			else if (0 < i)
				option = &args[1][i];
			else
				*has_path = TRUE;
		}
		if (*has_path == TRUE || option)
			break ;
	}
	return ((char *)option);
}

static void
	env_with_args(char **args)
{
	char	*option;
	t_bool	has_path;

	has_path = FALSE;
	option = check_args(args, &has_path);
	if (has_path == FALSE && option)
	{
		g_ms.status = STATUS_GENERAL_ERR;
		put_enverror_with_option(option);
	}
	else if (has_path == TRUE || option)
	{
		g_ms.status = STATUS_GENERAL_ERR;
		ft_put_cmderror_with_help("env", CMD_ENV_HELP);
	}
}

static t_bool
	is_only_double_hyphen(char **args)
{
	return ((!ft_strcmp(args[1], "--") && !args[2]));
}

int
	ft_env(char **args)
{
	t_list	*envptr;

	g_ms.status = STATUS_SUCCESS;
	if (args[1] && !is_only_double_hyphen(args))
		env_with_args(args);
	else
	{
		envptr = g_ms.env;
		while (envptr)
		{
			if (ft_strchr(envptr->content, '='))
				ft_putendl_fd(envptr->content, STDOUT_FILENO);
			envptr = envptr->next;
		}
	}
	return (KEEP_RUNNING);
}
