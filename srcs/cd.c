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

t_bool
	validate_args(char **args)
{
	t_bool	ret;
	char	option[3];

	ret = FALSE;
	if (ft_get_cmd_option(option, *args))
	{
		ft_put_cmderror_with_arg("cd", CMD_OPTION_ERR, option);
		ft_put_cmderror_with_help("cd", CMD_CD_HELP);
	}
	else if (*args == NULL)
		ft_put_cmderror("cd", strerror(EINVAL));
	else if (**args != '\0')
		ret = TRUE;
	return (ret);
}

t_bool
	exec_cd(char **args)
{
	t_bool	ret;

	ret = FALSE;
	if (chdir(*args) != 0)
		ft_put_cmderror_with_arg("cd", strerror(errno), *args);
	else
		ret = TRUE;
	return (ret);
}

int
	ft_cd(char **args)
{
	args++;
	if (*args && !ft_strcmp(*args, "--"))
		args++;
	if (validate_args(args) == TRUE && exec_cd(args) == TRUE)
	{
		// TODO: $PWD、$OLDPWDの値を更新
		FREE(g_pwd);
		if (!(g_pwd = getcwd(NULL, 0)))
		{
			ft_putendl_fd(strerror(EINVAL), STDERR_FILENO);
			return (STOP);
		}
	}
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
	if (ft_init_pwd() == STOP)
		return (EXIT_FAILURE);
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
	{
		char	*pwdargs[2] = {"pwd", NULL};
		++args;
		ret = ft_pwd(pwdargs);
		ret = ft_cd(args);
		ret = ft_pwd(pwdargs);
	}
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
