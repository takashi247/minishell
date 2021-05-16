#include "minishell_tnishina.h"
#include "minishell_sikeda.h"
#include "libft.h"

static void
	handle_prior_signal(int signal)
{
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", STDERR_FILENO);
		ft_putstr_fd(PROMPT, STDERR_FILENO);
		g_ms.interrupted = TRUE;
		g_status = 1;
	}
}

void
	ft_sig_prior(void)
{
	if (signal(SIGINT, handle_prior_signal) == SIG_ERR)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		exit(1);
	}
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		exit(1);
	}
}

static void
	handle_post_signal(int signal)
{
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", STDERR_FILENO);
		if (kill(g_latest_pid, 0) == 0)
			g_status = 130;
	}
	else if (signal == SIGQUIT)
	{
		if (kill(g_latest_pid, 0) == 0)
		{
			ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
			g_status = 131;
		}
	}
}

void
	ft_sig_post(void)
{
	if (signal(SIGINT, handle_post_signal) == SIG_ERR)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		exit(1);
	}
	if (signal(SIGQUIT, handle_post_signal) == SIG_ERR)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		exit(1);
	}
}
