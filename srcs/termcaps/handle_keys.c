#include "minishell_tnishina.h"

int
	ft_handle_keys(const char *buf, char *pre_line,
		size_t *len, size_t *allocated)
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
		return (ft_backspace(pre_line, len));
	else if (ft_isprint(*buf) && buf[1] == '\0')
		return (ft_input_char(buf, pre_line, len, allocated));
	return (GNL_SUCCESS);
}
