#include "minishell_sikeda.h"

extern char
	*g_pwd;

int
	ft_init_pwd()
{
	int	fd;

	if ((g_pwd = ft_getenv("PWD")))
		if (0 <= (fd = open(g_pwd, O_RDONLY)) && close(fd))
			return (KEEP_RUNNING);
	if ((g_pwd = getcwd(NULL, 0)))
	{
		// TODO: $PWDの値を更新
		return (KEEP_RUNNING);
	}
	ft_putendl_fd(strerror(EINVAL), STDERR_FILENO);
	return (STOP);
}

int
	ft_pwd(char **args)
{
	char	*dir;
	char	option[3];

	dir = NULL;
	if (ft_get_cmd_option(option, args[1]))
	{
		ft_put_cmderror_with_arg("pwd", CMD_OPTION_ERR, option);
		ft_put_cmderror_with_help("pwd", CMD_PWD_HELP);
	}
	else
		ft_putendl_fd(g_pwd, STDOUT_FILENO);
	return (KEEP_RUNNING);
}

#ifdef PWDTEST
int
	main(int ac, char **av)
{
	char		**args;
	int			ret;
	int			i;

	if (ac < 2)
	{
		ft_put_cmderror("main", strerror(EINVAL));
		return (EXIT_FAILURE);
	}
	if (ft_init_pwd() == STOP)
		return (EXIT_FAILURE);
	if (!(args = (char **)malloc(sizeof(char*) * (ac + 1))))
		return (EXIT_FAILURE);
	i = -1;
	while (++i < ac)
		args[i] = av[i];
	args[i] = NULL;
	ret = 0;
	if (!ft_strcmp(args[1], "cd"))
	{
		++args;
		ret = ft_pwd(args);
		ret = ft_cd(args);
		ret = ft_pwd(args);
	}
	else if (!ft_strcmp(args[1], "pwd"))
		ret = ft_pwd(++args);
	if (ret == STOP)
	{
		// TODO: exitが呼ばれたときにSTOPが返されてloopを終了してmainが終了するイメージ
	}
	g_pwd ? FREE(g_pwd) : g_pwd;
	// system("leaks pwd.out");
	return (EXIT_SUCCESS);
}
#endif
