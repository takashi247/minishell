#include "minishell.h"

void
	ft_save_fds(t_command *c, int std_fds[3])
{
	if (c->redirects)
	{
		std_fds[0] = dup(STDIN_FILENO);
		std_fds[1] = dup(STDOUT_FILENO);
		std_fds[2] = dup(STDERR_FILENO);
		if (std_fds[0] < 0 || std_fds[1] < 0 || std_fds[2] < 0)
			ft_exit_n_free_g_vars(STATUS_GENERAL_ERR);
	}
}

void
	ft_restore_fds(t_command *c, int std_fds[3])
{
	if (c->redirects)
	{
		if (dup2(std_fds[0], STDIN_FILENO) < 0
			|| dup2(std_fds[1], STDOUT_FILENO) < 0
			|| dup2(std_fds[2], STDERR_FILENO) < 0)
			ft_exit_n_free_g_vars(STATUS_GENERAL_ERR);
		if (std_fds[0] != STDIN_FILENO)
			close(std_fds[0]);
		if (std_fds[1] != STDOUT_FILENO)
			close(std_fds[1]);
		if (std_fds[2] != STDERR_FILENO)
			close(std_fds[2]);
	}
}

t_bool
	ft_is_valid_path(const char *path)
{
	while (*path)
	{
		if (*path == ' ' || *path == '\t')
			return (FALSE);
		path++;
	}
	return (TRUE);
}

t_bool
	ft_check_param_error(int fd_from, char *path, char *redirect_op)
{
	t_bool	res;

	res = ft_has_env_in_path(path);
	if (fd_from <= GENERAL_ERROR || FD_MAX < fd_from || res)
	{
		if (fd_from == OVER_INT_RANGE || (FD_MAX < fd_from && !res))
			ft_put_fderror(fd_from, res);
		else if (res)
			ft_put_cmderror(path, AMBIGUOUS_REDIRECT_ERR_MSG);
		g_ms.status = STATUS_GENERAL_ERR;
		ft_free(&path);
		ft_free(&redirect_op);
		return (FALSE);
	}
	return (TRUE);
}

t_bool
	ft_validate_path(t_list *rd, char **path, char *pre_exp, int res)
{
	if (res == ENV_DELETED)
		*path = pre_exp;
	else if (res == COMPLETED)
	{
		if (ft_is_valid_path((char *)(rd->next->content)))
		{
			ft_free(&pre_exp);
			*path = ft_strdup((char *)(rd->next->content));
			if (!*path)
			{
				g_ms.status = STATUS_GENERAL_ERR;
				return (FALSE);
			}
		}
		else
			*path = pre_exp;
	}
	return (TRUE);
}
