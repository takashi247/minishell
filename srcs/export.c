#include "minishell_sikeda.h"

static int
	stop_with_puterror(const int err)
{
	g_status = STATUS_GENERAL_ERR;
	ft_put_error(strerror(err));
	return (STOP);
}

static t_bool
	validate_name(const char *arg)
{
	t_bool	ret;

	ret = TRUE;
	if (!arg)
		return (ret);
	if (!ft_isalpha(*arg) && *arg != '_')
		return (FALSE);
	arg++;
	while (*arg && *arg != '=' && ret == TRUE)
	{
		if (!ft_isalnum(*arg) && *arg != '_')
			ret = FALSE;
		arg++;
	}
	return (ret);
}

static void
	put_env_with_export_syntax(const char *str, const int fd)
{
	if (!str)
		return ;
	ft_putstr_fd("declare -x ", fd);
	while (*str && *str != '=')
		ft_putchar_fd(*str++, fd);
	if (*str++ == '=')
	{
		ft_putstr_fd("=\"", fd);
		while (*str)
		{
			if (*str == '"' || *str == '$' || *str == '\\' || *str == '`')
				ft_putchar_fd('\\', fd);
			ft_putchar_fd(*str++, fd);
		}
		ft_putstr_fd("\"\n", fd);
	}
	else
		ft_putchar_fd('\n', fd);
}

static int
	show_export(void)
{
	t_list	*copy_env;
	t_list	*copy_env_head;

	if (!(copy_env = ft_copy_env()))
		return (UTIL_ERROR);
	ft_envsort(&copy_env);
	copy_env_head = copy_env;
	while (copy_env)
	{
		put_env_with_export_syntax(copy_env->content, STDOUT_FILENO);
		copy_env = copy_env->next;
	}
	ft_clear_copied_env(&copy_env_head);
	return (UTIL_SUCCESS);
}

static char
	*get_name(const char *str)
{
	char	*name;
	char	*ret;
	size_t	len;

	len = 0;
	while (str[len] && str[len] != '=')
		len++;
	if (!(name = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ret = name;
	while (*str && *str != '=')
		*name++ = *str++;
	*name = '\0';
	return (ret);
}

static char
	*get_value(const char *str)
{
	char	*value;
	char	*ret;
	size_t	len;

	while (*str && *str != '=')
		str++;
	if (*str == '=')
		str++;
	len = 0;
	while (str[len])
		len++;
	if (!(value = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ret = value;
	while (*str)
		*value++ = *str++;
	*value = '\0';
	return (ret);
}

static t_bool
	is_plus_mode(char *name)
{
	size_t	len;

	len = ft_strlen(name);
	if (len && name[len - 1] == '+')
	{
		name[len - 1] = '\0';
		if (ft_getenv(name))
			return (TRUE);
	}
	return (FALSE);
}

static int
	exec_setenv(char **args, const char *name, const t_bool plus_mode)
{
	char	*value;
	char	*join;
	int		ret;

	value = NULL;
	if (ft_strchr(args[1], '=') && !(value = get_value(args[1])))
		return (STOP);
	ret = KEEP_RUNNING;
	if (plus_mode == FALSE && (!ft_getenv(name) || ft_strchr(args[1], '=')))
	{
		if (ft_setenv_sep(name, value) == UTIL_ERROR)
			ret = STOP;
#ifdef EXPORTTEST
		else
			show_export();	// テスト用にexport実行
#endif
	}
	else if (plus_mode == TRUE)
	{
		join = ft_getenv(name);
		if (join && !(join = ft_strjoin(join, value)))
			ret = STOP;
		else if (join)
		{
			FREE(value);
			value = join;
		}
		if (join && ft_setenv_sep(name, value) == UTIL_ERROR)
			ret = STOP;
#ifdef EXPORTTEST
		if (ret == KEEP_RUNNING)
			show_export();	// テスト用にexport実行
#endif
	}
	FREE(value);
	return (ret);
}

static int
	exec_export(char **args)
{
	char	*name;
	t_bool	plus_mode;

	while (args[1])
	{
		if (!(name = get_name(args[1])))
			return (stop_with_puterror(errno));
		plus_mode = is_plus_mode(name);
		if (validate_name(name) == FALSE)
		{
			g_status = STATUS_GENERAL_ERR;
			ft_put_cmderror_with_quoted_arg("export", CMD_IDENTIFIER_ERR, args++[1]);
		}
		else if (exec_setenv(args++, name, plus_mode) == STOP)
		{
			FREE(name);
			return (stop_with_puterror(errno));
		}
		FREE(name);
	}
	return (KEEP_RUNNING);
}

int
	ft_export(char **args)
{
	char	option[3];

	g_status = STATUS_SUCCESS;
	if (args[1] && !ft_strcmp(args[1], "--"))
		args++;
	else if (ft_get_cmd_option(option, args[1]))
	{
		g_status = STATUS_MISUSE_OF_BUILTINS_ERR;
		ft_put_cmderror_with_arg("export", CMD_OPTION_ERR, option);
		ft_put_cmderror_with_help("export", CMD_EXPORT_HELP);
		return (KEEP_RUNNING);
	}
	if (!args[1] && show_export() == UTIL_ERROR)
		return (stop_with_puterror(errno));
	return (exec_export(args));
}

#ifdef EXPORTTEST
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
	// system("leaks export.out");
	return (g_status);
}
#endif
