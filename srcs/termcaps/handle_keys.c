#include "minishell_tnishina.h"

int
	ft_handle_keys(const char *buf, char *pre_line, size_t *len, size_t *allocated)
{
	if (*buf == '\n' || *buf == '\r')
	{
		write(STDERR_FILENO, "\n", 1);
		tputs(g_ms.terminfo.def.cr, 1, ft_putchar);
		return (GNL_EOF);
	}
	else if (*buf == C_EOF && !*len)
	{
		*len = ft_strlen("exit");
		ft_strlcpy(pre_line, "exit", *len + 1);
		return (GNL_EOF);
	}
	else if (*buf == C_DEL && 0 < *len)
	{
		(*len)--;
		ft_backspace(pre_line, *len);
	}
	else if (ft_isprint(*buf) && buf[1] == '\0')
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
		if (g_ms.terminfo.prev.col == g_ms.terminfo.maxcol - 1
			&& g_ms.terminfo.prev.row == g_ms.terminfo.maxrow - 1)
			g_ms.terminfo.start.row--;
	}
	return (GNL_SUCCESS);
}
