#include "minishell_tnishina.h"

int
	ft_backspace(const char *pre_line, size_t len)
{
	int	col;
	int	row;

	col = g_ms.terminfo.start.col;
	row = g_ms.terminfo.start.row;
	tputs(tgoto(g_ms.terminfo.def.cm, col, row), 1, ft_putchar);
	tputs(g_ms.terminfo.def.ce, 1, ft_putchar);
	ft_putstr_fd(PROMPT, STDERR_FILENO);
	write(STDERR_FILENO, pre_line, len);
	ft_update_current_position();
	write(1, "\x1b[0J", 4);
	return (UTIL_SUCCESS);
}
