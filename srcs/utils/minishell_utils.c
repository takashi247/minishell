#include "minishell_tnishina.h"

void
	ft_exit_n_free_g_vars(int exit_status)
{
	ft_free(&g_ms.pwd);
	ft_free(&g_ms.err_arg);
	ft_free(&g_ms.err_msg);
	ft_free(&g_ms.sh_pwd);
	ft_free(&g_ms.sh_oldpwd);
	ft_lstclear(&g_ms.env, free);
	ft_clear_history(&g_ms.hist.last);
	exit(exit_status);
}
