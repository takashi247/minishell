#include "minishell_sikeda.h"

extern char
	*g_pwd;

int
	ft_init_pwd(void)
{
	if (!(g_pwd = getcwd(NULL, 0)))
	{
		ft_put_error(strerror(errno));
		return (STOP);
	}
	ft_setenv_sep("PWD", g_pwd);
	return (KEEP_RUNNING);
}

int
	ft_pwd(char **args)
{
	char	option[3];

	g_status = STATUS_SUCCESS;
	if (ft_get_cmd_option(option, args[1]))
	{
		g_status = STATUS_GENERAL_ERR;
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
	char		**args_head;
	int			ret;
	int			i;

	if (ac < 2)
	{
		ft_put_cmderror("main", strerror(EINVAL));
		return (EXIT_FAILURE);
	}
	if (ft_init_env() == STOP)
		return (EXIT_FAILURE);
	if (ft_init_pwd() == STOP)
	{
		ft_lstclear(&g_env, free);
		return (EXIT_FAILURE);
	}
	if (!(args = (char **)malloc(sizeof(char*) * (ac + 1))))
	{
		FREE(g_pwd);
		ft_lstclear(&g_env, free);
		return (EXIT_FAILURE);
	}
	i = -1;
	while (++i < ac)
		args[i] = av[i];
	args[i] = NULL;
	args_head = args;
	ret = 0;
	if (!ft_strcmp(args[1], "cd"))
	{
		++args;
		ret = ft_pwd(args);	// test
		ret = ft_cd(args);
		ret = ft_pwd(args);	// test
	}
	else if (!ft_strcmp(args[1], "pwd"))
		ret = ft_pwd(++args);
	else if (!ft_strcmp(args[1], "env"))
		ret = ft_env(++args);
	else if (!ft_strcmp(args[1], "export"))
		ret = ft_export(++args);
	else if (!ft_strcmp(args[1], "unset"))
		ret = ft_unset(++args);
	else if (!ft_strcmp(args[1], "exit"))
		ret = ft_exit(++args);
	if (ret == STOP)
	{
		// TODO: exitが呼ばれたときにSTOPが返されてloopを終了してmainが終了するイメージ
	}
	FREE(args_head);
	FREE(g_pwd);
	ft_lstclear(&g_env, free);
	// system("leaks pwd.out");
	return (g_status);
}
#endif
