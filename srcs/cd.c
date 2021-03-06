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
#ifdef CDTEST
	char	*debug_ls[] = {"pwd", NULL};

	lsh_launch(debug_ls);
#endif
	if (args[1] == NULL)
		ft_put_cmderror("cd", strerror(EINVAL));
	else if (chdir(args[1]) != 0)
		ft_put_cmderror_with_arg("cd", strerror(errno), args[1]);
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
	int		ret;
	int		i;

	if (ac < 2)
	{
		ft_put_cmderror("main", strerror(EINVAL));
		return (EXIT_FAILURE);
	}
	if (!(args = (char **)malloc(sizeof(char*) * (ac + 1))))
		return (EXIT_FAILURE);
	i = -1;
	while (++i < ac)
		args[i] = av[i];
	args[i] = NULL;
	ret = 0;
	if (!ft_strcmp(args[1], "cd"))
		ret = ft_cd(++args);
	if (ret == STOP)
	{
		// TODO: exitが呼ばれたときにSTOPが返されてloopを終了してmainが終了するイメージ
	}
	return (EXIT_SUCCESS);
}
#endif
