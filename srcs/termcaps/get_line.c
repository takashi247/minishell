#include "minishell_tnishina.h"

int
	ft_get_line(char **line)
{
	ssize_t	ret;
	size_t	len;
	char	*pre_line;

	if (!line)
		return (GNL_ERROR);
	*line = NULL;
	len = 0;
	pre_line = (char *)malloc(BUFFER_SIZE);
	if (!pre_line)
	{
		ft_put_error(strerror(errno));
		return (GNL_ERROR);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &g_ms.ms_term);
	if (ft_get_cursor_position(&(g_ms.terminfo.start.row),
			&(g_ms.terminfo.start.col)) == UTIL_ERROR)
		return (GNL_ERROR);
	ret = ft_handle_keys_loop(pre_line, &len);
	tcsetattr(STDIN_FILENO, TCSANOW, &g_ms.origin_term);
	if (0 <= ret)
		*line = ft_substr(pre_line, 0, len);
	ft_free(&pre_line);
	if ((0 <= ret && !*line) || ret < 0)
	{
		if (ret != IS_OVERFLOW)
			ft_put_error(strerror(errno));
		return (GNL_ERROR);
	}
	return (GNL_SUCCESS);
}
