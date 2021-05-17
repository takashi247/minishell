#include "minishell_sikeda.h"
#include "minishell_tnishina.h"

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
	if (ft_init_term() == UTIL_ERROR)
	{
		printf("error\n");
		ft_lstclear(&g_env, free);
		ft_free(&g_pwd);
		return (UTIL_ERROR);
	}
	g_ms.interrupted = FALSE;
	g_err_arg = NULL;
	g_err_msg = NULL;
	return (UTIL_SUCCESS);
}
