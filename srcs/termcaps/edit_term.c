#include "minishell_tnishina.h"

int
	ft_clear_line(void)
{
	tputs(tgetstr("dl", 0), 1, ft_putchar);
	tputs(tgetstr("cr", 0), 1, ft_putchar);
	ft_putstr_fd(PROMPT, STDOUT_FILENO);
	return (UTIL_SUCCESS);
}
