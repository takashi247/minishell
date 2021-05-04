#include "minishell_tnishina.h"

static int
	handle_keys(const char *buf, char *pre_line,
		size_t *len, size_t *allocated)
{
	ft_get_win_size();
	ft_update_current_position();
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
		return (ft_backspace(pre_line, len));
	else if (ft_isprint(*buf) && buf[1] == '\0')
		return (ft_input_char(buf, pre_line, len, allocated));
	return (GNL_SUCCESS);
}

int
	ft_handle_keys_loop(char *pre_line, size_t *len)
{
	char	buf[4];
	int		ret;
	size_t	allocated;

	ft_bzero(buf, sizeof(buf));
	allocated = BUFFER_SIZE;
	ft_putstr_fd(PROMPT, STDERR_FILENO);
	ret = read(STDIN_FILENO, buf, sizeof(buf) / sizeof(buf[0]));
	while (0 <= ret)
	{
		if (g_ms.interrupted == TRUE)
		{
			g_ms.interrupted = FALSE;
			*len = 0;
		}
		ret = handle_keys(buf, pre_line, len, &allocated);
		if (ret < 0 || ret == GNL_EOF)
			break ;
		ft_bzero(buf, sizeof(buf));
		ret = read(STDIN_FILENO, buf, sizeof(buf) / sizeof(buf[0]));
	}
	return (ret);
}
