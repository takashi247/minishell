#include "minishell_tnishina.h"
#include "minishell_sikeda.h"
#include "libft.h"

static void
	dup_to_stdfd(t_command *c, t_bool p_flag[2], int last_p[2], int new_p[2])
{
	if (p_flag[1])
	{
		close(last_p[1]);
		if (dup2(last_p[0], STDIN_FILENO) < 0)
			ft_exit_n_free_g_vars(STATUS_GENERAL_ERR);
		close(last_p[0]);
	}
	if (p_flag[0])
	{
		close(new_p[0]);
		if (c->args && dup2(new_p[1], STDOUT_FILENO) < 0)
			ft_exit_n_free_g_vars(STATUS_GENERAL_ERR);
		close(new_p[1]);
	}
}

static void
	execute_child(t_command *c, int std_fds[3])
{
	if (ft_is_builtin(c))
	{
		ft_execute_builtin(TRUE, c);
		ft_exit_n_free_g_vars(g_status);
	}
	else
	{
		ft_save_fds(c, std_fds);
		if (ft_set_redirection(c->redirects, std_fds) && c->args)
			ft_do_command(c);
		else
			ft_exit_n_free_g_vars(g_status);
	}
}

static void
	update_pipes(t_bool pipe_flag[2], int lastpipe[2], int newpipe[2])
{
	if (pipe_flag[1])
	{
		close(lastpipe[0]);
		close(lastpipe[1]);
	}
	if (pipe_flag[0])
	{
		lastpipe[0] = newpipe[0];
		lastpipe[1] = newpipe[1];
	}
}

static void
	start_command(t_command *c, t_bool p_flag[2], int l_pipe[2])
{
	pid_t	pid;
	int		newpipe[2];
	int		std_fds[3];

	p_flag[0] = ft_is_pipe(c);
	if (p_flag[0])
		pipe(newpipe);
	ft_sig_pipe();
	pid = fork();
	if (pid == 0)
	{
		dup_to_stdfd(c, p_flag, l_pipe, newpipe);
		execute_child(c, std_fds);
	}
	update_pipes(p_flag, l_pipe, newpipe);
	c->pid = pid;
	p_flag[1] = ft_is_pipe(c);
}

/*
** pipe_flag[0]: a flag to denote if a command's operator is a pipe
** pipe_flag[1]: a flag to denote if a command is piped from the previous one
*/

t_command
	*ft_execute_pipeline(t_command *c)
{
	t_bool	pipe_flag[2];
	int		lastpipe[2];
	int		res;

	res = COMPLETED;
	pipe_flag[1] = FALSE;
	ft_memset(lastpipe, -1, sizeof(lastpipe));
	while (c && res != REDIRECT_DELETED)
	{
		res = ft_expand_env_var(c);
		if (res == COMPLETED)
		{
			start_command(c, pipe_flag, lastpipe);
			if (pipe_flag[1])
				c = c->next;
			else
				break ;
		}
		else if (res == REDIRECT_DELETED)
			c = c->next;
		else
			return (NULL);
	}
	return (c);
}
