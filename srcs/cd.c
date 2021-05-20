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
