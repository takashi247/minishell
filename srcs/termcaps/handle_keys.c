#include "minishell_tnishina.h"

static int
	handle_keys(const char *buf, size_t *allocated)
{
	ft_get_win_size();
	ft_update_current_position();
	if (*buf == '\n' || *buf == '\r')
	{
		write(STDERR_FILENO, "\n", 1);
		tputs(g_ms.terminfo.def.cr, 1, ft_putchar);
		if (0 < g_ms.hist.input_len)
			ft_add_history(&g_ms.hist, g_ms.hist.input, g_ms.hist.input_len);
		g_ms.hist.current = NULL;
		return (GNL_EOF);
	}
	else if (*buf == C_EOF && !g_ms.hist.input_len)
	{
		g_ms.hist.input_len = ft_strlen("exit");
		ft_free(&g_ms.hist.input);
		g_ms.hist.input = ft_strdup("exit");
		return (GNL_EOF);
	}
	else if (*buf == C_DEL && 0 < g_ms.hist.input_len)
		return (ft_backspace());
	else if (!ft_strcmp(buf, K_UP))
		return (ft_up_history(allocated));
	else if (!ft_strcmp(buf, K_DOWN))
		return (ft_down_history(allocated));
	else if (ft_isprint(*buf) && buf[1] == '\0')
		return (ft_input_char(buf, allocated));
	return (GNL_SUCCESS);
}

int
	ft_handle_keys_loop(void)
{
	char	buf[4];
	int		ret;
	size_t	allocated;

	ft_bzero(buf, sizeof(buf));
	allocated = BUFFER_SIZE;
	g_ms.hist.current = NULL;
	ft_putstr_fd(PROMPT, STDERR_FILENO);
	ret = read(STDIN_FILENO, buf, sizeof(buf) / sizeof(buf[0]));
	while (0 <= ret)
	{
		if (g_ms.interrupted == TRUE)
		{
			g_ms.interrupted = FALSE;
			g_ms.hist.input_len = 0;
		}
		ret = handle_keys(buf, &allocated);
		if (ret < 0 || ret == GNL_EOF)
			break ;
		ft_bzero(buf, sizeof(buf));
		ret = read(STDIN_FILENO, buf, sizeof(buf) / sizeof(buf[0]));
	}
	return (ret);
}
