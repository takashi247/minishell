#include "minishell.h"

#ifdef WITH_GNL
int
	init_minishell(int ac)
{
	(void)ac;
	if (ft_init_env() == STOP)
		return (UTIL_ERROR);
	if (ft_init_pwd() == STOP)
	{
		ft_lstclear(&g_ms.env, free);
		return (UTIL_ERROR);
	}
	g_ms.err_arg = NULL;
	g_ms.err_msg = NULL;
	return (UTIL_SUCCESS);
}

#else
int
	init_minishell(int ac)
{
	if (ft_init_env() == STOP)
		return (UTIL_ERROR);
	if (ft_init_pwd() == STOP)
	{
		ft_lstclear(&g_ms.env, free);
		return (UTIL_ERROR);
	}
	if (ac == 1)
	{
		if (ft_init_term() == UTIL_ERROR)
		{
			printf("error\n");
			ft_lstclear(&g_ms.env, free);
			ft_free(&g_ms.pwd);
			return (UTIL_ERROR);
		}
		g_ms.interrupted = FALSE;
	}
	g_ms.err_arg = NULL;
	g_ms.err_msg = NULL;
	return (UTIL_SUCCESS);
}
#endif
