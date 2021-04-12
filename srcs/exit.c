#include "minishell_sikeda.h"

static int
	exit_with_args(char **args)
{
	char	*trimmed_arg;

	if (!(trimmed_arg = ft_strtrim(args[1], SPACE_CHARS)))
	{
		ft_put_error(strerror(errno));
		return (STOP);
	}
	if (ft_isnumeric(trimmed_arg) && !ft_isover_llrange(trimmed_arg))
	{
		g_status = (uint8_t)ft_atoi(trimmed_arg);
		if (args[2])
		{
			ft_put_cmderror("exit", "too many arguments");
			g_status = STATUS_GENERAL_ERR;
			FREE(trimmed_arg);
			return (KEEP_RUNNING);
		}
	}
	else
	{
		ft_put_cmderror_with_arg("exit", "numeric argument required", args[1]);
		g_status = STATUS_OUT_OF_RANGE_ERR;
	}
	FREE(trimmed_arg);
	return (STOP);
}

int
	ft_exit(char **args)
{
	ft_putendl_fd("exit", STDERR_FILENO);
	if (args[1])
	{
		if (!ft_strcmp(args[1], "--"))
		{
			if (!args[2])
				return (STOP);
			args++;
		}
		g_status = STATUS_GENERAL_ERR;
		return (exit_with_args(args));
	}
	return (STOP);
}

#ifdef EXITTEST
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
		ret = ft_pwd(args);
		ret = ft_cd(args);
		ret = ft_pwd(args);
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
	// system("leaks exit.out");
	return (g_status);
}
#endif
