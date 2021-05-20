#include "minishell_tnishina.h"

static int
	get_definition_from_termcap(void)
{
	g_ms.terminfo.def.cm = tgetstr("cm", 0);
	g_ms.terminfo.def.cd = tgetstr("cd", 0);
	g_ms.terminfo.def.cr = tgetstr("cr", 0);
	g_ms.terminfo.def.sf = tgetstr("sf", 0);
	if (!g_ms.terminfo.def.cm
		|| !g_ms.terminfo.def.cd
		|| !g_ms.terminfo.def.cr
		|| !g_ms.terminfo.def.sf)
		return (UTIL_ERROR);
	return (UTIL_SUCCESS);
}

static void
	set_settings(void)
{
	g_ms.ms_term.c_lflag &= ~(ICANON | ECHO);
	g_ms.ms_term.c_cc[VMIN] = 1;
	g_ms.ms_term.c_cc[VTIME] = 0;
}

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
	ft_get_win_size();
	if (get_definition_from_termcap() == UTIL_ERROR)
		return (UTIL_ERROR);
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
	set_settings();
	return (UTIL_SUCCESS);
}
