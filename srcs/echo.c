#include "minishell_sikeda.h"
#include "minishell_tnishina.h"

static t_bool
	has_n_option(const char *args)
{
	if (args && *args++ == '-')
	{
		if (*args == '\0')
			return (FALSE);
		while (*args == 'n')
			args++;
		if (*args == '\0')
			return (TRUE);
	}
	return (FALSE);
}

int
	ft_echo(char **args)
{
	int	is_n;

	is_n = FALSE;
	while (has_n_option(args[1]))
	{
		is_n = TRUE;
		args++;
	}
	if (args[1])
	{
		ft_putstr_fd(args[1], STDOUT_FILENO);
		args++;
	}
	while (args[1])
	{
		ft_putchar_fd(' ', STDOUT_FILENO);
		ft_putstr_fd(args[1], STDOUT_FILENO);
		args++;
	}
	if (is_n == FALSE)
		ft_putchar_fd('\n', STDOUT_FILENO);
	g_ms.status = STATUS_SUCCESS;
	return (KEEP_RUNNING);
}
