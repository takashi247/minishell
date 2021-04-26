#include "test_builtin.h"

int
	test_cd(char **args, const t_bool is_nodir)
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

int
	test_cdnodir(char **args)
{
	const char	*args1[] = {"mkdir", "cdtest", NULL};
	const char	*args2[] = {"cd", "cdtest", NULL};
	const char	*args3[] = {"rmdir", "../cdtest", NULL};
	int			ret;

	test_launch((char **)args1);
	ret = ft_cd((char **)args2);
	test_launch((char **)args3);
	ret = test_cd(args, TRUE);
	return (ret);
}

int
	test_cdnodir2(char **args)
{
	const char	*args1[] = {"mkdir", "cdtest", NULL};
	const char	*args2[] = {"cd", "cdtest", NULL};
	const char	*args3[] = {"rmdir", "../cdtest", NULL};
	const char	*args4[] = {"cd", "..", NULL};
	int			ret;

	test_launch((char **)args1);
	ret = ft_cd((char **)args2);
	test_launch((char **)args3);
	ret = test_cd(args, FALSE);
	ret = test_cd((char **)args4, TRUE);
	return (ret);
}

int
	test_cd_and_pwd(char **args)
{
	int	ret;

	ret = ft_pwd(args);
	ret = ft_cd(args);
	ret = ft_pwd(args);
	return (ret);
}
