#include "minishell_sikeda.h"

static t_bool
	validate_args(const char *args)
{
	t_bool	ret;
	char	option[3];

	ret = TRUE;
	if (ft_get_cmd_option(option, args))
	{
		ft_put_cmderror_with_arg("cd", CMD_OPTION_ERR, option);
		ft_put_cmderror_with_help("cd", CMD_CD_HELP);
		ret = FALSE;
	}
	return (ret);
}

static char
	*get_home_path(const char *args)
{
	char	*path;

	if (!args)
	{
		path = ft_getenv("HOME");
		if (!path)
		{
			ft_put_cmderror("cd", "HOME not set");
			return (NULL);
		}
		return (path);
	}
	return ((char *)args);
}

static t_bool
	exec_cd(const char *path, const char *args)
{
	t_bool	ret;

	ret = FALSE;
	if (!path)
		return (ret);
	if (chdir(path) != 0)
	{
		if (args)
			ft_put_cmderror_with_arg("cd", strerror(errno), (char *)args);
		else
			ft_put_cmderror_with_arg("cd", strerror(errno), (char *)path);
	}
	else
		ret = TRUE;
	return (ret);
}

static t_bool
	update_path_env(const char *input_path)
{
	char	*oldpwd;

	if (ft_getenv("OLDPWD") && ft_setenv_sep("OLDPWD", g_pwd) == UTIL_ERROR)
	{
		ft_put_cmderror("cd", strerror(errno));
		return (FALSE);
	}
	oldpwd = g_pwd;
	g_pwd = ft_make_full_path(input_path);
	ft_free(&oldpwd);
	if (!g_pwd
		|| (ft_getenv("PWD") && ft_setenv_sep("PWD", g_pwd) == UTIL_ERROR))
	{
		ft_put_cmderror("cd", strerror(errno));
		return (FALSE);
	}
	return (TRUE);
}

int
	ft_cd(char **args)
{
	char	*path;

	g_status = STATUS_GENERAL_ERR;
	args++;
	if (*args && !ft_strcmp(*args, "--"))
		args++;
	if (validate_args(*args) == FALSE)
		return (KEEP_RUNNING);
	if (*args && **args == '\0')
		path = g_pwd;
	else
		path = *args;
	path = get_home_path(path);
	if (exec_cd(path, *args) == TRUE)
	{
		if (update_path_env(path) == FALSE)
			return (STOP);
		g_status = STATUS_SUCCESS;
	}
	return (KEEP_RUNNING);
}
