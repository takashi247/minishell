#include "minishell_sikeda.h"

int
	init_minishell(void)
{
	if (ft_init_env() == STOP)
		return (UTIL_ERROR);
	if (ft_init_pwd() == STOP)
	{
		ft_lstclear(&g_env, free);
		return (UTIL_ERROR);
	}
	g_ms.interrupted = FALSE;
	return (UTIL_SUCCESS);
}
