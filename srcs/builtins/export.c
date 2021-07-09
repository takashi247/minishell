#include "minishell.h"

static int
	stop_with_puterror(const int err)
{
	g_ms.status = STATUS_GENERAL_ERR;
	ft_put_error(strerror(err));
	return (STOP);
}

t_bool
	ft_validate_name(const char *arg)
{
	t_bool	ret;

	ret = TRUE;
	if (!arg)
		return (ret);
	if (!ft_isalpha(*arg) && *arg != '_')
		return (FALSE);
	arg++;
	while (*arg && *arg != '=' && ret == TRUE)
	{
		if (!ft_isalnum(*arg) && *arg != '_')
			ret = FALSE;
		arg++;
	}
	return (ret);
}

static t_bool
	is_plus_mode(const char *arg, char *name)
{
	size_t	len;

	len = ft_strlen(name);
	if (len && name[len - 1] == '+' && arg[len] == '=')
	{
		name[len - 1] = '\0';
		if (ft_getenv(name))
			return (TRUE);
	}
	return (FALSE);
}

static int
	exec_export(char **args)
{
	char	*name;
	t_bool	plus_mode;

	while (args[1])
	{
		name = ft_extract_envname_from_str(args[1]);
		if (!name)
			return (stop_with_puterror(errno));
		plus_mode = is_plus_mode(args[1], name);
		if (ft_validate_name(name) == FALSE)
		{
			g_ms.status = STATUS_GENERAL_ERR;
			ft_put_cmderror_with_quoted_arg(
				"export", CMD_IDENTIFIER_ERR, args++[1]);
		}
		else if (ft_export_setenv(args++, name, plus_mode) == STOP)
		{
			ft_free(&name);
			return (stop_with_puterror(errno));
		}
		ft_free(&name);
	}
	return (KEEP_RUNNING);
}

int
	ft_export(char **args)
{
	char	option[3];

	g_ms.status = STATUS_SUCCESS;
	if (args[1] && !ft_strcmp(args[1], "--"))
		args++;
	else if (ft_get_cmd_option(option, args[1]))
	{
		g_ms.status = STATUS_MISUSE_OF_BUILTINS_ERR;
		ft_put_cmderror_with_arg("export", CMD_OPTION_ERR, option);
		ft_put_cmderror_with_help("export", CMD_EXPORT_HELP);
		return (KEEP_RUNNING);
	}
	if (!args[1] && ft_print_export() == UTIL_ERROR)
		return (stop_with_puterror(errno));
	return (exec_export(args));
}
