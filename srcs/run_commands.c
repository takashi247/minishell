#include "minishell.h"

t_bool
	ft_is_pipe(t_command *c)
{
	if (!ft_strcmp(c->op, "|"))
		return (TRUE);
	else
		return (FALSE);
}

t_bool
	ft_is_builtin(t_command *c)
{
	if (c->args
		&& (!ft_strcmp((char *)(c->args->content), "echo")
		|| !ft_strcmp((char *)(c->args->content), "cd")
		|| !ft_strcmp((char *)(c->args->content), "pwd")
		|| !ft_strcmp((char *)(c->args->content), "export")
		|| !ft_strcmp((char *)(c->args->content), "unset")
		|| !ft_strcmp((char *)(c->args->content), "env")
		|| !ft_strcmp((char *)(c->args->content), "exit")))
		return (TRUE);
	else
		return (FALSE);
}

static t_bool
	wait_pipeline(pid_t pid)
{
	int		term_status;

	g_ms.latest_pid = pid;
	if (waitpid(pid, &term_status, 0) < 0)
		return (FALSE);
	if (WIFEXITED(term_status))
		g_ms.status = WEXITSTATUS(term_status);
	else if (WIFSIGNALED(term_status))
		ft_handle_post_pipe_signal(WTERMSIG(term_status));
	while (wait(NULL) > 0)
		;
	ft_sig_post();
	return (TRUE);
}

void
	ft_run_commands(t_command *commands, int *res)
{
	int			expand_res;
	t_command	*c;

	c = commands;
	while (c)
	{
		expand_res = ft_expand_env_var(c);
		if (expand_res == FAILED)
			ft_exit_n_free_g_vars(STATUS_GENERAL_ERR);
		else if (expand_res == COMPLETED && (c->args || c->redirects))
		{
			if (ft_is_builtin(c) && !ft_is_pipe(c))
			{
				*res = ft_execute_builtin(FALSE, c);
				if (*res != KEEP_RUNNING)
					break ;
				c = c->next;
				continue ;
			}
			c = ft_execute_pipeline(c);
			if (!c || !wait_pipeline(c->pid))
				ft_exit_n_free_g_vars(STATUS_GENERAL_ERR);
		}
		c = c->next;
	}
}
