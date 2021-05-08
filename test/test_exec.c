#include "test_builtin.h"

int
	test_export(char **args)
{
	const char	*export_test[] = {"export", NULL};
	int			ret;
	t_bool		need_export;

	need_export = FALSE;
	if (args[1] && ft_strcmp(args[1], "--"))
		need_export = TRUE;
	ret = ft_export(args++);
	if (g_status == EXIT_SUCCESS && need_export == TRUE)
		ft_export((char **)export_test);
	return (ret);
}

int
	test_commands(char **args)
{
	int	ret;

	ret = KEEP_RUNNING;
	if (!ft_strcmp(args[1], "echo"))
		ret = ft_echo(++args);
	else if (!ft_strcmp(args[1], "cd"))
		ret = test_cd(++args, FALSE);
	else if (!ft_strcmp(args[1], "cd_nodir"))
		ret = test_cdnodir(++args);
	else if (!ft_strcmp(args[1], "cd_nodir2"))
		ret = test_cdnodir2(++args);
	else if (!ft_strcmp(args[1], "pwd"))
		ret = ft_pwd(++args);
	else if (!ft_strcmp(args[1], "cd_pwd"))
		ret = test_cd_and_pwd(++args);
	else if (!ft_strcmp(args[1], "env"))
		ret = ft_env(++args);
	else if (!ft_strcmp(args[1], "export"))
		ret = test_export(++args);
	else if (!ft_strcmp(args[1], "unset"))
		ret = ft_unset(++args);
	else if (!ft_strcmp(args[1], "exit"))
		ret = ft_exit(++args);
	return (ret);
}
