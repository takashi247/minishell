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
	if (tcgetattr(STDIN_FILENO, &g_ms.ms_term) != 0)
	{
		ft_put_error(strerror(errno));
		return (UTIL_ERROR);
	}
	if (tcgetattr(STDIN_FILENO, &g_ms.origin_term) != 0)
	{
		ft_put_error(strerror(errno));
		return (UTIL_ERROR);
	}
	g_ms.ms_term.c_lflag &= ~(ICANON | ECHO);
	g_ms.ms_term.c_cc[VMIN] = 1;
	g_ms.ms_term.c_cc[VTIME] = 0;
	return (UTIL_SUCCESS);
}
