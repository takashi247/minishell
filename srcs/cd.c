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

static t_bool
	validate_args(const char *args)
{
	t_bool	ret;
	char	option[3];

	ret = TRUE;
	if (ft_get_cmd_option(option, args))
	{
		ft_put_cmderror_with_arg("cd", CMD_OPTION_ERR, option);
		ft_put_cmderror_with_help("cd", CMD_CD_HELP);
		ret = FALSE;
	}
	return (ret);
}

static char
	*get_path(const char *args)
{
	char	*path;

	if (!args)
	{
		if (!(path = ft_getenv("HOME")))
		{
			ft_put_cmderror("cd", "HOME not set");
			return (NULL);
		}
		return (path);
	}
	return ((char*)args);
}

static t_bool
	exec_cd(char *path, char *args)
{
	t_bool	ret;

	ret = FALSE;
	if (!path)
		return (ret);
	if (chdir(path) != 0)
		ft_put_cmderror_with_arg("cd", strerror(errno), args);
	else
		ret = TRUE;
	return (ret);
}

static t_bool
	update_path_env(void)
{
	if (ft_getenv("OLDPWD") && ft_setenv_sep("OLDPWD", g_pwd) == UTIL_ERROR)
	{
		ft_put_cmderror("cd", strerror(errno));
		return (FALSE);
	}
	FREE(g_pwd);
	if (!(g_pwd = getcwd(NULL, 0))
	|| (ft_getenv("PWD") && ft_setenv_sep("PWD", g_pwd) == UTIL_ERROR))
	{
		ft_put_cmderror("cd", strerror(errno));
		return (FALSE);
	}
	return (TRUE);
}

int
	ft_cd(char **args)
{
	char	*path;

	g_status = STATUS_GENERAL_ERR;
	args++;
	if (*args && !ft_strcmp(*args, "--"))
		args++;
	if (validate_args(*args) == FALSE)
		return (KEEP_RUNNING);
	if (*args && **args == '\0')
		path = g_pwd;
	else
		path = *args;
	if (exec_cd(get_path(path), *args) == TRUE)
	{
		if (update_path_env() == FALSE)
			return (STOP);
		g_status = STATUS_SUCCESS;
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
	if (!ft_strcmp(args[1], "cd"))
	{
		ret = ft_cd(++args);
		if (g_status == STATUS_SUCCESS)
		{
			char	*pwdargs[] = {"pwd", NULL};
			ft_pwd(pwdargs);
			printf("PWD: %s\n", ft_getenv("PWD"));
			printf("OLDPWD: %s\n", ft_getenv("OLDPWD"));
		}
	}
	else if (!ft_strcmp(args[1], "cd_nodir"))
	{
		char		*args1[] = {"mkdir", "cdtest", NULL};
		lsh_launch(args1);
		fflush(stdout);
		char		*args2[] = {"cd", "cdtest", NULL};
		ret = ft_cd(args2);
		char		*args3[] = {"rmdir", "../cdtest", NULL};
		lsh_launch(args3);
		char		*args4[] = {"cd", "", NULL};
		ret = ft_cd(args4);
		char	*pwdargs[] = {"pwd", NULL};
		ft_pwd(pwdargs);
		printf("PWD: %s\n", ft_getenv("PWD"));
		printf("OLDPWD: %s\n", ft_getenv("OLDPWD"));
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
	// system("leaks cd.out");
	return (g_status);
}
#endif
