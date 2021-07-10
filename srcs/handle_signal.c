#include "minishell.h"

static void
	handle_prior_signal(int signal)
{
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", STDERR_FILENO);
		ft_putstr_fd(PROMPT, STDERR_FILENO);
		g_ms.interrupted = TRUE;
		g_ms.status = STATUS_GENERAL_ERR;
		g_ms.hist.input_len = 0;
	}
}

void
	ft_sig_prior(void)
{
	if (signal(SIGINT, handle_prior_signal) == SIG_ERR)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		exit(STATUS_GENERAL_ERR);
	}
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		exit(STATUS_GENERAL_ERR);
	}
}

static void
	handle_post_signal(int signal)
{
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", STDERR_FILENO);
		if (kill(g_ms.latest_pid, 0) == 0)
			g_ms.status = STATUS_SIGINT;
	}
	else if (signal == SIGQUIT)
	{
		if (kill(g_ms.latest_pid, 0) == 0)
		{
			ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
			g_ms.status = STATUS_SIGQUIT;
		}
	}
}

void
	ft_sig_post(void)
{
	if (signal(SIGINT, handle_post_signal) == SIG_ERR)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		exit(STATUS_GENERAL_ERR);
	}
	if (signal(SIGQUIT, handle_post_signal) == SIG_ERR)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		exit(STATUS_GENERAL_ERR);
	}
}
