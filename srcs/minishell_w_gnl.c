#include "minishell_tnishina.h"

#ifdef WITH_GNL
static void
	put_escape_error(t_bool *ret)
{
	ft_put_cmderror("\\", MULTILINE_ERROR_MSG);
	g_ms.status = STATUS_GENERAL_ERR;
	*ret = FALSE;
}

static t_bool
	get_gnl_input(t_command **commands, int *res)
{
	char		*line;
	t_bool		ret;
	int			gnl_res;

	line = NULL;
	ft_putstr_fd(PROMPT, STDERR_FILENO);
	ft_sig_prior_w_gnl();
	gnl_res = ft_ms_get_next_line(&line);
	if (gnl_res == GNL_ERROR)
		ft_exit_n_free_g_vars(STATUS_GENERAL_ERR);
	else if (gnl_res == GNL_EOF)
	{
		*res = EXIT;
		ret = FALSE;
	}
	ft_sig_post();
	if (ft_is_end_with_escape(line))
		put_escape_error(&ret);
	else
	{
		ft_convert_line(&line, commands);
		ret = TRUE;
	}
	ft_free(&line);
	return (ret);
}

int
	main(int ac, char **av)
{
	t_command	*commands;
	int			res;

	if (!(ac == 1 || ac == 3))
		return (STATUS_GENERAL_ERR);
	if (init_minishell(ac) == UTIL_ERROR)
		return (EXIT_FAILURE);
	if (ac == 3)
		ft_run_commandline(av);
	while (1)
	{
		res = KEEP_RUNNING;
		if (get_gnl_input(&commands, &res))
		{
			ft_run_commands(commands, &res);
			ft_clear_commands(&commands);
		}
		if (res == EXIT || res == EXIT_NON_NUMERIC)
			break ;
	}
	ft_exit_n_free_g_vars(g_ms.status);
}
#endif
