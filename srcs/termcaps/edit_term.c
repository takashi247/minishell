#include "minishell_tnishina.h"

void
	put_line(const char *pre_line, size_t len)
{
	int	row;

	row = g_ms.terminfo.start.row;
	tputs(tgoto(g_ms.terminfo.def.cm, 0, row), 1, ft_putchar);
	tputs(g_ms.terminfo.def.cd, 1, ft_putchar);
	ft_putstr_fd(PROMPT, STDERR_FILENO);
	write(STDERR_FILENO, pre_line, len);
}

int
	ft_enter(void)
{
	write(STDERR_FILENO, "\n", 1);
	tputs(g_ms.terminfo.def.cr, 1, ft_putchar);
	if (0 < g_ms.hist.input_len)
		ft_add_history(&g_ms.hist, g_ms.hist.input, g_ms.hist.input_len);
	g_ms.hist.current = NULL;
	return (GNL_EOF);
}

int
	ft_backspace(void)
{
	g_ms.hist.input_len--;
	put_line(g_ms.hist.input, g_ms.hist.input_len);
	if (g_ms.terminfo.current.col == 1)
	{
		tputs(tgoto(g_ms.terminfo.def.cm, 0, g_ms.terminfo.current.row),
			1, ft_putchar);
	}
	return (GNL_SUCCESS);
}

static int
	check_allocated_and_realloc(size_t *allocated)
{
	if (SIZE_MAX == g_ms.hist.input_len
		|| *allocated < g_ms.hist.input_len + 1)
	{
		if (SIZE_MAX == g_ms.hist.input_len
			|| SIZE_MAX - BUFFER_SIZE < *allocated)
			return (IS_OVERFLOW);
		g_ms.hist.input
			= ft_realloc(g_ms.hist.input, *allocated + BUFFER_SIZE, *allocated);
		if (!g_ms.hist.input)
		{
			write(STDERR_FILENO, "\n", 1);
			tputs(g_ms.terminfo.def.cr, 1, ft_putchar);
			return (GNL_ERROR);
		}
		*allocated += BUFFER_SIZE;
	}
	return (GNL_SUCCESS);
}

int
	ft_input_char(const char *buf, size_t *allocated)
{
	int	ret;

	ret = check_allocated_and_realloc(allocated);
	if (ret != GNL_SUCCESS)
		return (ret);
	write(STDERR_FILENO, buf, 1);
	g_ms.hist.input[g_ms.hist.input_len] = *buf;
	g_ms.hist.input_len++;
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
