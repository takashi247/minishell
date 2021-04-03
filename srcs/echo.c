#include "minishell_sikeda.h"

int
	ft_echo(t_list *args)
{
	int	is_n;

	is_n = FALSE;
	if (args && !ft_strcmp(args->content, "-n"))
	{
		is_n = TRUE;
		args = args->next;
	}
	if (args)
	{
		ft_putstr_fd(args->content, STDOUT_FILENO);
		args = args->next;
	}
	while (args)
	{
		ft_putchar_fd(' ', STDOUT_FILENO);
		ft_putstr_fd(args->content, STDOUT_FILENO);
		args = args->next;
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
	t_list	*args;
	t_list	*args_head;
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
	args_head = NULL;
	i = 1;
	while (i < ac)
	{
		if (!(args = ft_lstnew(ft_strdup(av[i]))))
		{
			FREE(g_pwd);
			ft_lstclear(&g_env, free);
			ft_lstclear(&args_head, free);
			return (EXIT_FAILURE);
		}
		ft_lstadd_back(&args_head, args);
		i++;
	}
	ret = 0;
	if (!ft_strcmp(args_head->content, "echo"))
		ret = ft_echo(args_head->next);
	if (ret == STOP)
	{
		// TODO: exitが呼ばれたときにSTOPが返されてloopを終了してmainが終了するイメージ
	}
	FREE(g_pwd);
	ft_lstclear(&args_head, free);
	ft_lstclear(&g_env, free);
	// system("leaks echo.out");
	return (g_status);
}
#endif
