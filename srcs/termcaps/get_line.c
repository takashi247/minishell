#include "minishell_tnishina.h"

static int
	init_input_and_position(void)
{
	g_ms.hist.input = (char *)malloc(BUFFER_SIZE);
	if (!g_ms.hist.input)
	{
		ft_put_error(strerror(errno));
		return (GNL_ERROR);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &g_ms.ms_term);
	if (ft_get_cursor_position(&(g_ms.terminfo.start.row),
			&(g_ms.terminfo.start.col)) == UTIL_ERROR)
	{
		ft_free(&g_ms.hist.input);
		return (GNL_ERROR);
	}
	return (GNL_SUCCESS);
}

int
	ft_get_line(char **line, t_bool is_heredoc)
{
	ssize_t	ret;

	if (!line)
		return (GNL_ERROR);
	*line = NULL;
	if (init_input_and_position() == GNL_ERROR)
		return (GNL_SUCCESS);
	ret = ft_handle_keys_loop(is_heredoc);
	tcsetattr(STDIN_FILENO, TCSANOW, &g_ms.origin_term);
	if (0 <= ret)
		*line = ft_strndup_append_null(g_ms.hist.input, g_ms.hist.input_len);
	ft_free(&g_ms.hist.input);
	g_ms.hist.input_len = 0;
	if (ret == GNL_HEREDOC_EOF)
		return (GNL_HEREDOC_EOF);
	if ((0 <= ret && !*line) || ret < 0)
	{
		if (ret != IS_OVERFLOW)
			ft_put_error(strerror(errno));
		return (GNL_ERROR);
	}
	return (GNL_SUCCESS);
}
