#include "minishell_tnishina.h"
#include "minishell_sikeda.h"
#include "libft.h"

void
	sig_int_prior()
{
	ft_putstr_fd("\n", STDERR_FILENO);
	ft_putstr_fd(PROMPT, STDERR_FILENO);
	g_status = 1;
}

void
	sig_int_post()
{
	ft_putstr_fd("\n", STDERR_FILENO);
	g_status = 130;
}

void
	sig_quit_post()
{
	ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
	g_status = 131;
}

void
	ft_sig_prior(void)
{
	if (signal(SIGINT, sig_int_prior) == SIG_ERR)
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

void
	ft_sig_post(void)
{
	if (signal(SIGINT, sig_int_post) == SIG_ERR)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		exit(1);
	}
	if (signal(SIGQUIT, sig_quit_post) == SIG_ERR)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		exit(1);
	}
}
