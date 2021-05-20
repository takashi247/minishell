#include "minishell_sikeda.h"

int
	ft_init_pwd(void)
{
	g_pwd = getcwd(NULL, 0);
	if (!g_pwd || ft_setenv_sep("PWD", g_pwd) == UTIL_ERROR)
	{
		ft_put_error(strerror(errno));
		ft_free(&g_pwd);
		return (STOP);
	}
	g_ms.sh_pwd = ft_strdup(g_pwd);
	if (!g_ms.sh_pwd)
	{
		ft_put_error(strerror(errno));
		ft_free(&g_pwd);
		return (STOP);
	}
	g_ms.sh_oldpwd = NULL;
	return (KEEP_RUNNING);
}

int
	ft_pwd(char **args)
{
	char	option[3];

	g_status = STATUS_SUCCESS;
	if (args[1] && !ft_strcmp(args[1], "--"))
		args++;
	else if (ft_get_cmd_option(option, args[1]))
	{
		g_status = STATUS_GENERAL_ERR;
		ft_put_cmderror_with_arg("pwd", CMD_OPTION_ERR, option);
		ft_put_cmderror_with_help("pwd", CMD_PWD_HELP);
		return (KEEP_RUNNING);
	}
	ft_putendl_fd(g_pwd, STDOUT_FILENO);
	return (KEEP_RUNNING);
}
