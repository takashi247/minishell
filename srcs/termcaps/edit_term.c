#include "minishell_tnishina.h"

int
	ft_backspace(const char *pre_line, size_t len)
{
	int	row;

	row = g_ms.terminfo.start.row;
	tputs(tgoto(g_ms.terminfo.def.cm, 0, row), 1, ft_putchar);
	tputs(g_ms.terminfo.def.cd, 1, ft_putchar);
	ft_putstr_fd(PROMPT, STDERR_FILENO);
	write(STDERR_FILENO, pre_line, len);
	return (UTIL_SUCCESS);
}
