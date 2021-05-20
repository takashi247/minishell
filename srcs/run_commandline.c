#include "minishell_sikeda.h"
#include "minishell_tnishina.h"
#include "libft.h"

static void
	get_commandline_input(char *input, t_command **commands)
{
	char	*line;

	line = ft_strdup(input);
	if (!line)
		ft_exit_n_free_g_vars(STATUS_GENERAL_ERR);
	ft_sig_post();
	if (ft_is_end_with_escape(line))
		ft_put_cmderror("\\", MULTILINE_ERROR_MSG);
	else
		ft_convert_line(&line, commands);
	ft_free(&line);
}

void
	ft_run_commandline(char **av)
{
	t_command	*commands;
	t_command	*head;
	int			res;

	if (!ft_strcmp("-c", av[1]))
	{
		res = KEEP_RUNNING;
		get_commandline_input(av[2], &commands);
		head = commands;
		ft_run_commands(commands, &res);
		ft_clear_commands(&head);
	}
	else
		g_status = STATUS_GENERAL_ERR;
	ft_exit_n_free_g_vars(g_status);
}
