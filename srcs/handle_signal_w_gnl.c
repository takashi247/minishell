#include "minishell_tnishina.h"

static void
	handle_prior_signal(int signal)
{
	if (signal == SIGINT)
	{
		ft_putstr_fd("\b\b  \b\n", STDERR_FILENO);
		ft_putstr_fd(PROMPT, STDERR_FILENO);
		g_ms.status = 1;
	}
	else if (signal == SIGQUIT)
		ft_putstr_fd("\b\b  \b\b", STDERR_FILENO);
}

void
	ft_sig_prior_w_gnl(void)
{
	if (signal(SIGINT, handle_prior_signal) == SIG_ERR)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		exit(1);
	}
	if (signal(SIGQUIT, handle_prior_signal) == SIG_ERR)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		exit(1);
	}
}
