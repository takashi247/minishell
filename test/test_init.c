#include "test_builtin.h"

int
	test_init_minishell(void)
{
	if (ft_init_env() == STOP)
		return (EXIT_FAILURE);
	if (ft_init_pwd() == STOP)
	{
		ft_lstclear(&g_env, free);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

#ifdef LEAKS
static void
	exec_leaks(void)
{
	system("leaks builtin.out");
}

#else
static void
	exec_leaks(void)
{
}
#endif

int
	test_finalize_minishell(char ***args_head, const int exit_code)
{
	if (*args_head)
	{
		free(*args_head);
		*args_head = NULL;
	}
	if (g_pwd)
		ft_free(&g_pwd);
	if (g_env)
		ft_lstclear(&g_env, free);
	exec_leaks();
	exit(exit_code);
}
