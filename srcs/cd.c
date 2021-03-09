#include "minishell_sikeda.h"

#ifdef CDTEST
int
	lsh_launch(char **args)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;

	if ((pid = fork()) < 0)
		perror("lsh");
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
			perror("lsh");
		exit(EXIT_FAILURE);
	} else {
		do
		{
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (1);
}
#endif

int
	ft_cd(char **args)
{
	char	option[3];
	int		i;

#ifdef CDTEST
	char	*debug_ls[] = {"pwd", NULL};

	lsh_launch(debug_ls);
#endif
	i = 1;
	if (args[i] && !ft_strcmp(args[i], "--"))
		i++;
	if (ft_get_cmd_option(option, args[i]))
	{
		ft_put_cmderror_with_arg("cd", CMD_OPTION_ERR, option);
		ft_put_cmderror_with_help("cd", CMD_CD_HELP);
	}
	else if (args[i] == NULL)
		ft_put_cmderror("cd", strerror(EINVAL));
	else if (chdir(args[i]) != 0)
		ft_put_cmderror_with_arg("cd", strerror(errno), args[i]);
#ifdef CDTEST
	lsh_launch(debug_ls);
#endif
	return (KEEP_RUNNING);
}

#ifdef CDTEST
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
	if (!(args = (char **)malloc(sizeof(char*) * (ac + 1))))
	{
		FREE(g_pwd);
		return (EXIT_FAILURE);
	}
	i = -1;
	while (++i < ac)
		args[i] = av[i];
	args[i] = NULL;
	args_head = args;
	ret = 0;
	if (!ft_strcmp(args[1], "cd"))
		ret = ft_cd(++args);
	else if (!ft_strcmp(args[1], "pwd"))
		ret = ft_pwd(++args);
	if (ret == STOP)
	{
		// TODO: exitが呼ばれたときにSTOPが返されてloopを終了してmainが終了するイメージ
	}
	FREE(args_head);
	FREE(g_pwd);
	// system("leaks cd.out");
	return (EXIT_SUCCESS);
}
#endif
