#include "test_builtin.h"

static int
	exec_cd_test(char **args, const t_bool is_nodir)
{
	const char	*pwdargs[] = {"pwd", NULL};
	int			ret;

	ret = ft_cd(args);
	if (g_status == STATUS_SUCCESS || is_nodir == TRUE)
	{
		ft_pwd((char **)pwdargs);
		printf("PWD: %s\n", ft_getenv("PWD"));
		printf("OLDPWD: %s\n", ft_getenv("OLDPWD"));
	}
	return (ret);
}

static int
	exec_cdnodir_test(char **args)
{
	const char	*args1[] = {"mkdir", "cdtest", NULL};
	const char	*args2[] = {"cd", "cdtest", NULL};
	const char	*args3[] = {"rmdir", "../cdtest", NULL};
	const char	*args4[] = {"cd", "", NULL};
	int			ret;

	(void)args;
	test_launch((char **)args1);
	ret = ft_cd((char **)args2);
	test_launch((char **)args3);
	exec_cd_test((char **)args4, TRUE);
	return (ret);
}

static int
	exec_cd_and_pwd(char **args)
{
	int	ret;

	ret = ft_pwd(args);
	ret = ft_cd(args);
	ret = ft_pwd(args);
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
		ret = exec_cd_test(++args, FALSE);
	else if (!ft_strcmp(args[1], "cd_nodir"))
		ret = exec_cdnodir_test(++args);
	else if (!ft_strcmp(args[1], "pwd"))
		ret = ft_pwd(++args);
	else if (!ft_strcmp(args[1], "cd_pwd"))
		ret = exec_cd_and_pwd(++args);
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
