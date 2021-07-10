#include "minishell.h"

void
	ft_handle_post_pipe_signal(int signal)
{
	if (signal == SIGINT)
		ft_putstr_fd("\n", STDERR_FILENO);
	else if (signal == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
}

static void
	handle_piped_signal(int signal)
{
	if (signal == SIGINT)
	{
		if (kill(g_ms.latest_pid, 0) == 0)
			g_ms.status = STATUS_SIGINT;
		else
			ft_putstr_fd("\n", STDERR_FILENO);
	}
	else if (signal == SIGQUIT)
	{
		if (kill(g_ms.latest_pid, 0) == 0)
			g_ms.status = STATUS_SIGQUIT;
	}
}

void
	ft_sig_pipe(void)
{
	if (signal(SIGINT, handle_piped_signal) == SIG_ERR)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		exit(STATUS_GENERAL_ERR);
	}
	if (signal(SIGQUIT, handle_piped_signal) == SIG_ERR)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		exit(STATUS_GENERAL_ERR);
	}
}
