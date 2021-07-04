#include "minishell_tnishina.h"

static t_bool
	append_redirect_out(int fd_from, char *path, int std_fds[3])
{
	int	fd_to;

	fd_to = open(path, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd_to < 0)
	{
		ft_put_cmderror(path, strerror(errno));
		g_ms.status = STATUS_GENERAL_ERR;
		return (FALSE);
	}
	if (fd_from == NO_FD_SETTING)
		fd_from = STDOUT_FILENO;
	else if (fd_from == std_fds[0])
		std_fds[0] = dup(fd_from);
	else if (fd_from == std_fds[1])
		std_fds[1] = dup(fd_from);
	else if (fd_from == std_fds[2])
		std_fds[2] = dup(fd_from);
	if (std_fds[0] < 0 || std_fds[1] < 0 || std_fds[2] < 0)
		ft_exit_n_free_g_vars(STATUS_GENERAL_ERR);
	if (dup2(fd_to, fd_from) < 0)
		ft_exit_n_free_g_vars(STATUS_GENERAL_ERR);
	if (fd_to != fd_from)
		close(fd_to);
	return (TRUE);
}

static t_bool
	redirect_out(int fd_from, char *path, int std_fds[3])
{
	int	fd_to;

	fd_to = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd_to < 0)
	{
		ft_put_cmderror(path, strerror(errno));
		g_ms.status = STATUS_GENERAL_ERR;
		return (FALSE);
	}
	if (fd_from == NO_FD_SETTING)
		fd_from = STDOUT_FILENO;
	else if (fd_from == std_fds[0])
		std_fds[0] = dup(fd_from);
	else if (fd_from == std_fds[1])
		std_fds[1] = dup(fd_from);
	else if (fd_from == std_fds[2])
		std_fds[2] = dup(fd_from);
	if (std_fds[0] < 0 || std_fds[1] < 0 || std_fds[2] < 0)
		ft_exit_n_free_g_vars(STATUS_GENERAL_ERR);
	if (dup2(fd_to, fd_from) < 0)
		ft_exit_n_free_g_vars(STATUS_GENERAL_ERR);
	if (fd_to != fd_from)
		close(fd_to);
	return (TRUE);
}

static t_bool
	redirect_in(int fd_from, char *path, int std_fds[3])
{
	int	fd_to;

	fd_to = open(path, O_RDONLY);
	if (fd_to < 0)
	{
		ft_put_cmderror(path, strerror(errno));
		g_ms.status = STATUS_GENERAL_ERR;
		return (FALSE);
	}
	if (fd_from == NO_FD_SETTING)
		fd_from = STDIN_FILENO;
	else if (fd_from == std_fds[0])
		std_fds[0] = dup(fd_from);
	else if (fd_from == std_fds[1])
		std_fds[1] = dup(fd_from);
	else if (fd_from == std_fds[2])
		std_fds[2] = dup(fd_from);
	if (std_fds[0] < 0 || std_fds[1] < 0 || std_fds[2] < 0)
		ft_exit_n_free_g_vars(STATUS_GENERAL_ERR);
	if (dup2(fd_to, fd_from) < 0)
		ft_exit_n_free_g_vars(STATUS_GENERAL_ERR);
	if (fd_to != fd_from)
		close(fd_to);
	return (TRUE);
}

t_bool
	ft_execute_redirection(int fd, char *op, char *path, int stdfds[3])
{
	if (!(ft_strcmp(op, APPEND_REDIRECT_OUT)))
		return (append_redirect_out(fd, path, stdfds));
	else if (!(ft_strcmp(op, REDIRECT_OUT)))
		return (redirect_out(fd, path, stdfds));
	else if (!(ft_strcmp(op, HEREDOC)))
		return (redirect_in(fd, HEREDOC_PATH, stdfds));
	else if (!(ft_strcmp(op, REDIRECT_IN)))
		return (redirect_in(fd, path, stdfds));
	else
		return (FALSE);
}
