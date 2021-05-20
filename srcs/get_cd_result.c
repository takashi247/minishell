#include "minishell_tnishina.h"
#include "libft.h"

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

static int
	update_pwd(const char *input_path)
{
	char	*cwd;

	ft_free(&g_ms.sh_oldpwd);
	g_ms.sh_oldpwd = g_ms.pwd;
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		ft_free(&cwd);
		g_ms.pwd = ft_make_full_path(input_path);
	}
	else
	{
		ft_put_cderror_no_current(errno);
		if (g_ms.pwd[ft_strlen(g_ms.pwd) - 1] == '/')
			g_ms.pwd = ft_strjoin(g_ms.pwd, input_path);
		else
			g_ms.pwd = ft_join_path(g_ms.pwd, input_path);
	}
	ft_free(&g_ms.sh_pwd);
	g_ms.sh_pwd = ft_strdup(g_ms.pwd);
	if (!g_ms.sh_pwd)
		return (UTIL_ERROR);
	return (UTIL_SUCCESS);
}

static t_bool
	update_path_env(const char *input_path)
{
	char	*new_path;

	new_path = "";
	if (g_ms.sh_pwd)
		new_path = g_ms.sh_pwd;
	if (ft_getenv("OLDPWD") && ft_setenv_sep("OLDPWD", new_path) == UTIL_ERROR)
	{
		ft_put_cmderror("cd", strerror(errno));
		return (FALSE);
	}
	if (update_pwd(input_path) == UTIL_ERROR)
	{
		ft_put_cmderror("cd", strerror(errno));
		return (FALSE);
	}
	if (!g_ms.pwd
		|| (ft_getenv("PWD") && ft_setenv_sep("PWD", g_ms.pwd) == UTIL_ERROR))
	{
		ft_put_cmderror("cd", strerror(errno));
		return (FALSE);
	}
	return (TRUE);
}

int
	ft_get_cd_result(char **path, const char *args)
{
	int		res;

	res = exec_cd(path, args);
	if (res == MALLOC_ERR
		|| ((res == CD_SUCCESS || res == CD_PATH_SUCCESS)
			&& update_path_env(*path) == FALSE))
	{
		if (res == MALLOC_ERR)
			ft_put_cmderror("cd", strerror(errno));
		ft_free(path);
		return (STOP);
	}
	if (res == CD_PATH_SUCCESS)
		ft_putendl_fd(g_ms.pwd, STDOUT_FILENO);
	if (res == CD_PATH_SUCCESS || res == CD_SUCCESS)
		g_ms.status = STATUS_SUCCESS;
	ft_free(path);
	return (KEEP_RUNNING);
}
