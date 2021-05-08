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

static void
	update_pwd(const char *input_path)
{
	char	*oldpwd;
	char	*cwd;

	oldpwd = g_pwd;
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		ft_free(&cwd);
		g_pwd = ft_make_full_path(input_path);
	}
	else
	{
		ft_put_cderror_no_current(errno);
		g_pwd = ft_join_path(g_pwd, input_path);
	}
	ft_free(&oldpwd);
}

static t_bool
	update_path_env(const char *input_path)
{
	if (ft_getenv("OLDPWD") && ft_setenv_sep("OLDPWD", g_pwd) == UTIL_ERROR)
	{
		ft_put_cmderror("cd", strerror(errno));
		return (FALSE);
	}
	update_pwd(input_path);
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
	path = ft_get_home_path(*args);
	if (!path)
		return (KEEP_RUNNING);
	if (path && *path == '\0')
		path = g_pwd;
	if (exec_cd(path, *args) == TRUE)
	{
		if (update_path_env(path) == FALSE)
			return (STOP);
		g_status = STATUS_SUCCESS;
	}
	return (KEEP_RUNNING);
}
