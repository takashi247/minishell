#include "minishell.h"

static int
	handle_keys(const char *buf, size_t *allocated, t_bool is_heredoc)
{
	ft_get_win_size();
	ft_update_current_position();
	if (*buf == C_EOF && !g_ms.hist.input_len)
	{
		g_ms.hist.input_len = ft_strlen("exit");
		ft_free(&g_ms.hist.input);
		g_ms.hist.input = ft_strdup("exit");
		if (is_heredoc)
			return (GNL_HEREDOC_EOF);
		return (GNL_EOF);
	}
	else if (*buf == '\n' || *buf == '\r')
		return (ft_enter(is_heredoc));
	else if (*buf == C_DEL && 0 < g_ms.hist.input_len)
		return (ft_backspace(is_heredoc));
	else if (!ft_strcmp(buf, K_UP))
		return (ft_up_history(allocated, is_heredoc));
	else if (!ft_strcmp(buf, K_DOWN))
		return (ft_down_history(allocated, is_heredoc));
	else if (ft_isprint(*buf) && buf[1] == '\0')
		return (ft_input_char(buf, allocated));
	return (GNL_SUCCESS);
}

static char
	*get_prompt(t_bool is_heredoc)
{
	if (is_heredoc == TRUE)
		return (HEREDOC_PROMPT);
	else
		return (PROMPT);
}

static int
	handle_put_prompt(size_t *allocated, t_bool is_heredoc)
{
	int	ret;

	ret = 1;
	if (g_ms.interrupted == TRUE)
		ret = handle_keys(g_ms.interrupted_buf, allocated, is_heredoc);
	else
		ft_putstr_fd(get_prompt(is_heredoc), STDERR_FILENO);
	g_ms.interrupted = FALSE;
	return (ret);
}

int
	ft_handle_keys_loop(t_bool is_heredoc)
{
	char	buf[4];
	int		ret;
	size_t	allocated;

	ft_bzero(buf, sizeof(buf));
	allocated = BUFFER_SIZE;
	g_ms.hist.current = NULL;
	ret = handle_put_prompt(&allocated, is_heredoc);
	if (ret < 0 || ret == GNL_EOF)
		return (ret);
	ret = read(STDIN_FILENO, buf, sizeof(buf) / sizeof(buf[0]));
	while (0 <= ret)
	{
		if (g_ms.interrupted == TRUE)
		{
			ft_memcpy(g_ms.interrupted_buf, buf, sizeof(buf));
			return (GNL_SIGINT);
		}
		ret = handle_keys(buf, &allocated, is_heredoc);
		if (ret < 0 || ret == GNL_EOF)
			break ;
		ft_bzero(buf, sizeof(buf));
		ret = read(STDIN_FILENO, buf, sizeof(buf) / sizeof(buf[0]));
	}
	return (ret);
}
