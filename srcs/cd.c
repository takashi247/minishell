#include "minishell_sikeda.h"
#include "minishell_tnishina.h"

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

static int
	exec_cd(char **path, const char *args)
{
	int		ret;
	char	*cd_path;

	if (!*path)
		return (CD_FAILED);
	cd_path = ft_getenv("CDPATH");
	if (cd_path && **path != '/' && **path != '.')
	{
		ret = ft_exec_cd_path(path, &cd_path);
		if (ret == CD_PATH_SUCCESS || ret == MALLOC_ERR || ret == CD_SUCCESS)
			return (ret);
	}
	if (chdir(*path) != 0)
	{
		ret = CD_FAILED;
		if (args)
			ft_put_cmderror_with_arg("cd", strerror(errno), (char *)args);
		else
			ft_put_cmderror_with_arg("cd", strerror(errno), (char *)(*path));
	}
	else
		ret = CD_SUCCESS;
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
		if (g_pwd[ft_strlen(g_pwd) - 1] == '/')
			g_pwd = ft_strjoin(g_pwd, input_path);
		else
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
	int		res;

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
	path = ft_strdup(path);
	if (!path)
	{
		ft_put_cmderror("cd", strerror(errno));
		return (STOP);
	}
	res = exec_cd(&path, *args);
	if (res == MALLOC_ERR
		|| ((res == CD_SUCCESS || res == CD_PATH_SUCCESS)
			&& update_path_env(path) == FALSE))
	{
		ft_free(&path);
		return (STOP);
	}
	if (res == CD_PATH_SUCCESS)
		ft_putendl_fd(g_pwd, STDOUT_FILENO);
	if (res == CD_PATH_SUCCESS || res == CD_SUCCESS)
		g_status = STATUS_SUCCESS;
	ft_free(&path);
	return (KEEP_RUNNING);
}
