#include "minishell_sikeda.h"

// debug
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

int
	ft_cd(char **args)
{
	char	*debug_ls[] = {"pwd", NULL};
	char	*path;

	lsh_launch(debug_ls);
	path = NULL;
	if (args[1] == NULL)
	{
		// TODO: 引数なしでcdが呼ばれた際にパスを~にしてもHOMEへ行かない、課題範囲外なので引数エラーを返してしまっても良い、調査・検討する
		path = "~";
	}
	else
		path = args[1];
	if (chdir(path) != 0)
		ft_put_cmdmsg_fd_with_arg("cd", strerror(errno), args[1], STDERR_FILENO);
	lsh_launch(debug_ls);
	return (1);
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
		ft_put_cmdmsg_fd("main", strerror(EINVAL), STDERR_FILENO);
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
	if (!ret)
	{
		// TODO: exitが呼ばれたときに0が返されてloopを終了してmainが終了するイメージ
	}
	return (EXIT_SUCCESS);
}
#endif
