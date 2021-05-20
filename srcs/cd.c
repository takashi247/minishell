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

// static t_bool
// 	exec_cd(const char *path, const char *args)
// {
// 	t_bool	ret;

// 	ret = FALSE;
// 	if (!path)
// 		return (ret);
// 	if (chdir(path) != 0)
// 	{
// 		if (args)
// 			ft_put_cmderror_with_arg("cd", strerror(errno), (char *)args);
// 		else
// 			ft_put_cmderror_with_arg("cd", strerror(errno), (char *)path);
// 	}
// 	else
// 		ret = TRUE;
// 	return (ret);
// }

// static int
// 	update_pwd(const char *input_path)
// {
// 	char	*cwd;

// 	ft_free(&g_ms.sh_oldpwd);
// 	g_ms.sh_oldpwd = g_pwd;
// 	cwd = getcwd(NULL, 0);
// 	if (cwd)
// 	{
// 		ft_free(&cwd);
// 		g_pwd = ft_make_full_path(input_path);
// 	}
// 	else
// 	{
// 		ft_put_cderror_no_current(errno);
// 		if (g_pwd[ft_strlen(g_pwd) - 1] == '/')
// 			g_pwd = ft_strjoin(g_pwd, input_path);
// 		else
// 			g_pwd = ft_join_path(g_pwd, input_path);
// 	}
// 	ft_free(&g_ms.sh_pwd);
// 	g_ms.sh_pwd = ft_strdup(g_pwd);
// 	if (!g_ms.sh_pwd)
// 		return (UTIL_ERROR);
// 	return (UTIL_SUCCESS);
// }

// static t_bool
// 	update_path_env(const char *input_path)
// {
// 	char	*new_path;

// 	new_path = "";
// 	if (g_ms.sh_pwd)
// 		new_path = g_ms.sh_pwd;
// 	if (ft_getenv("OLDPWD") && ft_setenv_sep("OLDPWD", new_path) == UTIL_ERROR)
// 	{
// 		ft_put_cmderror("cd", strerror(errno));
// 		return (FALSE);
// 	}
// 	if (update_pwd(input_path) == UTIL_ERROR)
// 	{
// 		ft_put_cmderror("cd", strerror(errno));
// 		return (FALSE);
// 	}
// 	if (!g_pwd
// 		|| (ft_getenv("PWD") && ft_setenv_sep("PWD", g_pwd) == UTIL_ERROR))
// 	{
// 		ft_put_cmderror("cd", strerror(errno));
// 		return (FALSE);
// 	}
// 	return (TRUE);
// }

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
	path = ft_strdup(path);
	if (!path)
	{
		ft_put_cmderror("cd", strerror(errno));
		return (STOP);
	}
	return (ft_get_cd_result(&path, *args));
}
