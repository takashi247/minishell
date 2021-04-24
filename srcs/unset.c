#include "minishell_sikeda.h"

static t_bool
	validate_arg(char *arg)
{
	t_bool	ret;

	ret = TRUE;
	if (!arg)
		return (ret);
	if (!ft_isalpha(*arg) && *arg != '_')
		return (FALSE);
	arg++;
	while (*arg && ret == TRUE)
	{
		if (!ft_isalnum(*arg) && *arg != '_')
			ret = FALSE;
		arg++;
	}
	return (ret);
}

#ifdef UNSETTEST
static void
	unsetenv_wrapper(const char *name)
{
	int		flag;
	char	*tmp;

	flag = 0;
	tmp = ft_getenv(name);
	if (tmp)
		flag = 1;
	ft_unsetenv(name);
	tmp = ft_getenv(name);
	if (!tmp && flag == 1)
		puts("\033[32munset success\033[0m");
}

#else
static void
	unsetenv_wrapper(const char *name)
{
	ft_unsetenv(name);
}
#endif

int
	ft_unset(char **args)
{
	char	option[3];

	g_status = STATUS_SUCCESS;
	if (args[1] && !ft_strcmp(args[1], "--"))
		args++;
	else if (ft_get_cmd_option(option, args[1]))
	{
		g_status = STATUS_MISUSE_OF_BUILTINS_ERR;
		ft_put_cmderror_with_arg("unset", CMD_OPTION_ERR, option);
		ft_put_cmderror_with_help("unset", CMD_UNSET_HELP);
		return (KEEP_RUNNING);
	}
	while (args[1])
	{
		if (!validate_arg(args[1]))
		{
			g_status = STATUS_GENERAL_ERR;
			ft_put_cmderror_with_quoted_arg(
				"unset", CMD_IDENTIFIER_ERR, args[1]);
		}
		else
			unsetenv_wrapper(args[1]);
		args++;
	}
	return (KEEP_RUNNING);
}
