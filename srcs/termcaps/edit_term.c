#include "minishell_tnishina.h"

int
	ft_backspace(const char *pre_line, size_t *len)
{
	int	row;

	(*len)--;
	row = g_ms.terminfo.start.row;
	tputs(tgoto(g_ms.terminfo.def.cm, 0, row), 1, ft_putchar);
	tputs(g_ms.terminfo.def.cd, 1, ft_putchar);
	ft_putstr_fd(PROMPT, STDERR_FILENO);
	write(STDERR_FILENO, pre_line, *len);
	return (GNL_SUCCESS);
}

int
	ft_input_char(const char *buf, char *pre_line,
		size_t *len, size_t *allocated)
{
	if (SIZE_MAX == *len || *allocated < *len + 1)
	{
		if (SIZE_MAX == *len || SIZE_MAX - BUFFER_SIZE < *allocated)
		{
			return (IS_OVERFLOW);
		}
		pre_line = ft_realloc(pre_line, *allocated + BUFFER_SIZE, *allocated);
		if (!pre_line)
		{
			write(STDERR_FILENO, "\n", 1);
			tputs(g_ms.terminfo.def.cr, 1, ft_putchar);
			return (GNL_ERROR);
		}
		*allocated += BUFFER_SIZE;
	}
	write(STDERR_FILENO, buf, 1);
	pre_line[*len] = *buf;
	(*len)++;
	if (g_ms.terminfo.current.col == g_ms.terminfo.maxcol)
	{
		tputs(tgoto(g_ms.terminfo.def.cm, 0, g_ms.terminfo.current.row + 1),
			1, ft_putchar);
		if (g_ms.terminfo.current.row == g_ms.terminfo.maxrow)
		{
			tputs(g_ms.terminfo.def.sf, 1, ft_putchar);
			g_ms.terminfo.start.row--;
		}
	}
	return (GNL_SUCCESS);
}
