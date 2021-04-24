#include "test_builtin.h"

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
		ret = ft_export(++args);
	else if (!ft_strcmp(args[1], "unset"))
		ret = ft_unset(++args);
	else if (!ft_strcmp(args[1], "exit"))
		ret = ft_exit(++args);
	return (ret);
}
