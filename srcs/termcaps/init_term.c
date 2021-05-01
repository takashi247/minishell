#include "minishell_sikeda.h"

int
	ft_init_term(void)
{
	char	*term_name;

	term_name = getenv("TERM");
	if (!term_name)
		term_name = "xterm-256color";
	if (tgetent(NULL, term_name) <= 0)
	{
		ft_put_error("Cannot find terminfo entry.");
		return (UTIL_ERROR);
	}
	if (tcgetattr(STDIN_FILENO, &g_ms.term) != 0)
	{
		ft_put_error(strerror(errno));
		return (UTIL_ERROR);
	}
	g_ms.term = g_ms.saved_term;
	g_ms.term.c_lflag &= ~(ICANON | ECHO);
	g_ms.term.c_cc[VMIN] = 1;
	g_ms.term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &g_ms.term);
	return (UTIL_SUCCESS);
}

int
	ft_finalize_term(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &g_ms.saved_term);
	return (UTIL_SUCCESS);
}
