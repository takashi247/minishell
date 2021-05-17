#include "minishell_tnishina.h"
#include "minishell_sikeda.h"
#include "libft.h"

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

	g_latest_pid = pid;
	if (waitpid(pid, &term_status, 0) < 0)
		return (FALSE);
	if (WIFEXITED(term_status))
		g_status = WEXITSTATUS(term_status);
	while (wait(NULL) > 0)
		;
	return (TRUE);
}

void
	ft_run_commands(t_command *c, char **environ, int *res)
{
	int			expand_res;

	*res = KEEP_RUNNING;
	while (c)
	{
		expand_res = ft_expand_env_var(c);
		if (expand_res == FAILED)
			ft_exit_n_free_g_vars(STATUS_GENERAL_ERR);
		else if (expand_res == COMPLETED && (c->args || c->redirects))
		{
			if (ft_is_builtin(c) && !ft_is_pipe(c))
			{
				*res = ft_execute_builtin(c);
				if (*res != KEEP_RUNNING)
					break ;
				c = c->next;
				continue ;
			}
			c = ft_execute_pipeline(c, environ);
			if (!c || !wait_pipeline(c->pid))
				ft_exit_n_free_g_vars(STATUS_GENERAL_ERR);
		}
		c = c->next;
	}
}
