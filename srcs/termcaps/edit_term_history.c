#include "minishell_tnishina.h"

static void
	adjust_start_row(t_bool is_heredoc)
{
	int64_t	total_len;
	int		need_rows;
	int		exist_rows;

	if (is_heredoc)
		total_len = g_ms.hist.input_len + ft_strlen(HEREDOC_PROMPT);
	else
		total_len = g_ms.hist.input_len + ft_strlen(PROMPT);
	exist_rows = g_ms.terminfo.maxrow - g_ms.terminfo.start.row + 1;
	need_rows = total_len / g_ms.terminfo.maxcol;
	if (0 < total_len % g_ms.terminfo.maxcol)
		need_rows++;
	need_rows -= exist_rows;
	while (0 < need_rows--)
	{
		tputs(g_ms.terminfo.def.sf, 1, ft_putchar);
		g_ms.terminfo.start.row--;
	}
}

int
	ft_up_history(size_t *allocated, t_bool is_heredoc)
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
	adjust_start_row(is_heredoc);
	ft_put_line(g_ms.hist.input, g_ms.hist.input_len, is_heredoc);
	return (GNL_SUCCESS);
}

int
	ft_down_history(size_t *allocated, t_bool is_heredoc)
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
	ft_put_line(g_ms.hist.input, g_ms.hist.input_len, is_heredoc);
	return (GNL_SUCCESS);
}
