#include "minishell_tnishina.h"
#include "libft.h"

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
	ft_check_param_error(int fd_from, char *path, char *redirect_op)
{
	if (fd_from <= TOKEN_ERROR || FD_MAX < fd_from || !redirect_op || !path)
	{
		if (fd_from == OVER_INT_RANGE || FD_MAX < fd_from)
			ft_put_fderror(fd_from);
		g_ms.status = STATUS_GENERAL_ERR;
		ft_free(&path);
		ft_free(&redirect_op);
		return (FALSE);
	}
	return (TRUE);
}
