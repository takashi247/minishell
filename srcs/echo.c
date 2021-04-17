#include "minishell_sikeda.h"

int
	ft_echo(char **args)
{
	int	is_n;

	is_n = FALSE;
	if (args[1] && !ft_strcmp(args[1], "-n"))
	{
		is_n = TRUE;
		args++;
	}
	if (args[1])
	{
		ft_putstr_fd(args[1], STDOUT_FILENO);
		args++;
	}
	while (args[1])
	{
		ft_putchar_fd(' ', STDOUT_FILENO);
		ft_putstr_fd(args[1], STDOUT_FILENO);
		args++;
	}
	if (is_n == FALSE)
		ft_putchar_fd('\n', STDOUT_FILENO);
	g_status = STATUS_SUCCESS;
	return (KEEP_RUNNING);
}

#ifdef ECHOTEST
int
	main(int ac, char **av)
{
	char	**args;
	char	**args_head;
	int		ret;
	int		i;

	if (ac < 2)
	{
		ft_put_error(strerror(EINVAL));
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
	if (!ft_strcmp(args[1], "echo"))
		ret = ft_echo(++args);
	else if (!ft_strcmp(args[1], "cd"))
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
	// system("leaks echo.out");
	return (g_status);
}
#endif
