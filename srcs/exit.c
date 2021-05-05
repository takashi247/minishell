#include "minishell_sikeda.h"

static int
	exit_with_args(char **args)
{
	char	*trimmed_arg;

	trimmed_arg = ft_strtrim(args[1], SPACE_CHARS);
	if (!trimmed_arg)
		ft_put_error(strerror(errno));
	else if (ft_isnumeric(trimmed_arg) && !ft_isover_llrange(trimmed_arg))
	{
		g_status = (uint8_t)ft_atoi(trimmed_arg);
		if (args[2])
		{
			ft_put_cmderror("exit", "too many arguments");
			g_status = STATUS_GENERAL_ERR;
			ft_free(&trimmed_arg);
			return (STOP);
		}
	}
	else
	{
		ft_put_cmderror_with_arg("exit", "numeric argument required", args[1]);
		g_status = STATUS_OUT_OF_RANGE_ERR;
	}
	if (trimmed_arg)
		ft_free(&trimmed_arg);
	return (EXIT);
}

int
	ft_exit(char **args)
{
	ft_putendl_fd("exit", STDERR_FILENO);
	if (args[1])
	{
		if (!ft_strcmp(args[1], "--"))
		{
			if (!args[2])
				return (EXIT);
			args++;
		}
		g_status = STATUS_GENERAL_ERR;
		return (exit_with_args(args));
	}
	return (EXIT);
}
