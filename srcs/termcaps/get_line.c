#include "minishell_tnishina.h"

int
	ft_get_line(char **line)
{
	ssize_t	rc;
	ssize_t	ret;
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
		ret = ft_handle_keys(buf, pre_line, &len, &allocated);
		if (ret < 0 || ret == GNL_EOF)
		{
			rc = ret;
			break ;
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
