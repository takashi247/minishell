#include "minishell_tnishina.h"

static void
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
	ft_up_history(size_t *allocated)
{
	if (!g_ms.hist.last)
		return (GNL_SUCCESS);
	if (!g_ms.hist.current)
		g_ms.hist.current = g_ms.hist.last;
	else if (g_ms.hist.current->prev)
		g_ms.hist.current = g_ms.hist.current->prev;
	else if (!g_ms.hist.current->prev)
		return (GNL_SUCCESS);
	ft_free(&g_ms.hist.input);
	g_ms.hist.input = ft_strdup(g_ms.hist.current->line);
	if (!g_ms.hist.input)
		return (GNL_ERROR);
	g_ms.hist.input_len = g_ms.hist.current->len;
	*allocated = g_ms.hist.input_len + 1;
	put_line(g_ms.hist.input, g_ms.hist.input_len);
	return (GNL_SUCCESS);
}

int
	ft_down_history(size_t *allocated)
{
	if (!g_ms.hist.current)
		return (GNL_SUCCESS);
	ft_free(&g_ms.hist.input);
	if (!g_ms.hist.current->next)
	{
		g_ms.hist.current = NULL;
		g_ms.hist.input = ft_strdup("");
		if (!g_ms.hist.input)
			return (GNL_ERROR);
		g_ms.hist.input_len = 0;
	}
	else
	{
		g_ms.hist.current = g_ms.hist.current->next;
		g_ms.hist.input = ft_strdup(g_ms.hist.current->line);
		if (!g_ms.hist.input)
			return (GNL_ERROR);
		g_ms.hist.input_len = g_ms.hist.current->len;
	}
	*allocated = g_ms.hist.input_len + 1;
	put_line(g_ms.hist.input, g_ms.hist.input_len);
	return (GNL_SUCCESS);
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

int
	ft_input_char(const char *buf, size_t *allocated)
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
