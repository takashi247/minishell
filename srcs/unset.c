#include "minishell_sikeda.h"

static t_bool
	validate_arg(char *arg)
{
	t_bool	ret;

	ret = TRUE;
	if (!arg)
		return (ret);
	if (!ft_isalpha(*arg) && *arg != '_')
		return (FALSE);
	arg++;
	while (*arg && ret == TRUE)
	{
		if (!ft_isalnum(*arg) && *arg != '_')
			ret = FALSE;
		arg++;
	}
	return (ret);
}

int
	ft_unset(char **args)
{
	char	option[3];

	g_status = STATUS_SUCCESS;
	if (args[1] && !ft_strcmp(args[1], "--"))
		args++;
	else if (ft_get_cmd_option(option, args[1]))
	{
		g_status = STATUS_MISUSE_OF_BUILTINS_ERR;
		ft_put_cmderror_with_arg("unset", CMD_OPTION_ERR, option);
		ft_put_cmderror_with_help("unset", CMD_UNSET_HELP);
		return (KEEP_RUNNING);
	}
	while (args[1])
	{
		if (!validate_arg(args[1]))
		{
			g_status = STATUS_GENERAL_ERR;
			ft_put_cmderror_with_quoted_arg("unset", CMD_IDENTIFIER_ERR, args[1]);
		}
#ifdef UNSETTEST
		else
		{
			int		flag = 0;
			char	*tmp = NULL;
			// 環境変数の存在チェック
			if ((tmp = ft_getenv(args[1])))
				flag = 1;
			// unset実行
			ft_unsetenv(args[1]);
			// 環境変数が消えたかチェック
			if (!(tmp = ft_getenv(args[1])) && flag == 1)
				puts("\033[32munset success\033[0m");
		}
#else
		else
			ft_unsetenv(args[1]);
#endif
		args++;
	}
	return (KEEP_RUNNING);
}

#ifdef UNSETTEST
int
	main(int ac, char **av)
{
	char	**args;
	char	**args_head;
	int		ret;
	int		i;

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
	// system("leaks unset.out");
	return (g_status);
}
#endif
