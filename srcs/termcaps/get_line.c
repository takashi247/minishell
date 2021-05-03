#include "minishell_tnishina.h"

int
	ft_get_line(char **line)
{
	ssize_t	rc;
	size_t	len;
	size_t	allocated;
	char	buf[4];
	char	*pre_line;

	if (!line)
		return (GNL_ERROR);
	*line = NULL;
	len = 0;
	ft_bzero(buf, sizeof(buf));
	pre_line = (char *)malloc(BUFFER_SIZE);
	allocated = BUFFER_SIZE;
	if (!pre_line)
	{
		ft_put_error(strerror(errno));
		return (GNL_ERROR);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &g_ms.ms_term);
	if (ft_get_cursor_position(
		&(g_ms.terminfo.start.row), &(g_ms.terminfo.start.col))
		== UTIL_ERROR)
		return (GNL_ERROR);
	ft_putstr_fd(PROMPT, STDERR_FILENO);
	rc = read(STDIN_FILENO, buf, sizeof(buf) / sizeof(buf[0]));
	while (0 <= rc)
	{
		ft_update_current_position();
		if (g_ms.interrupted == TRUE)
		{
			g_ms.interrupted = FALSE;
			len = 0;
		}
		if (*buf == '\n' || *buf == '\r')
		{
			write(STDERR_FILENO, "\n", 1);
			tputs(g_ms.terminfo.def.cr, 1, ft_putchar);
			break ;
		}
		else if (*buf == C_EOF && !len)
		{
			len = ft_strlen("exit");
			ft_strlcpy(pre_line, "exit", len + 1);
			break ;
		}
		else if (*buf == C_DEL && 0 < len)
		{
			len--;
			ft_backspace(pre_line, len);
		}
		else if (ft_isprint(*buf) && buf[1] == '\0')
		{
			if (SIZE_MAX == len || allocated < len + 1)
			{
				if (SIZE_MAX == len || SIZE_MAX - BUFFER_SIZE < allocated)
				{
					rc = IS_OVERFLOW;
					break ;
				}
				pre_line = ft_realloc(pre_line, allocated + BUFFER_SIZE, allocated);
				if (!pre_line)
				{
					write(STDERR_FILENO, "\n", 1);
					tputs(g_ms.terminfo.def.cr, 1, ft_putchar);
					rc = -1;
					break ;
				}
				allocated += BUFFER_SIZE;
			}
			write(STDERR_FILENO, buf, rc);
			pre_line[len] = *buf;
			len++;
			if (g_ms.terminfo.prev.col == g_ms.terminfo.maxcol - 1
				&& g_ms.terminfo.prev.row == g_ms.terminfo.maxrow - 1)
				g_ms.terminfo.start.row--;
		}
		ft_bzero(buf, sizeof(buf));
		rc = read(STDIN_FILENO, buf, sizeof(buf) / sizeof(buf[0]));
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &g_ms.origin_term);
	if (0 <= rc)
		*line = ft_substr(pre_line, 0, len);
	ft_free(&pre_line);
	if ((0 <= rc && !*line) || rc < 0)
	{
		if (rc != IS_OVERFLOW)
			ft_put_error(strerror(errno));
		return (GNL_ERROR);
	}
	return (GNL_SUCCESS);
}
