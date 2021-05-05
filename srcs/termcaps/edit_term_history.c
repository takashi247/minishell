#include "minishell_tnishina.h"

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
