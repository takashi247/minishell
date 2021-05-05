#include "minishell_tnishina.h"
#include "minishell_sikeda.h"
#include "libft.h"

void
	ft_save_fds(int std_fds[3])
{
	std_fds[0] = dup(STDIN_FILENO);
	std_fds[1] = dup(STDOUT_FILENO);
	std_fds[2] = dup(STDERR_FILENO);
}

void
	ft_restore_fds(int std_fds[3])
{
	dup2(std_fds[0], STDIN_FILENO);
	dup2(std_fds[1], STDOUT_FILENO);
	dup2(std_fds[2], STDERR_FILENO);
	close(std_fds[0]);
	close(std_fds[1]);
	close(std_fds[2]);
}

static int
	get_fd(char *arg)
{
	int		len;
	char	*fd_str;
	int		fd_num;

	if (!arg)
		return (TOKEN_ERROR);
	len = ft_strlen(arg);
	if (len == 1)
		return (NO_FD_SETTING);
	else if (arg[0] == '>')
		return (NO_FD_SETTING);
	else
	{
		if (ft_isdigit(arg[len - 2]))
			fd_str = ft_substr(arg, 0, len - 1);
		else
			fd_str = ft_substr(arg, 0, len - 2);
		if (ft_isover_intrange(fd_str))
			fd_num = OVER_INT_RANGE;
		else
			fd_num = ft_atoi(fd_str);
		ft_free(&fd_str);
		return (fd_num);
	}
}

static char
	*get_op(char *arg)
{
	if (!arg)
		return (NULL);
	while (ft_isdigit(*arg))
		arg++;
	return (ft_strdup(arg));
}

static t_bool
	append_redirect_out(int fd_from, char *path)
{
	int	fd_to;

	fd_to = open(path, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd_to < 0)
	{
		ft_put_cmderror(path, strerror(errno));
		g_status = STATUS_GENERAL_ERR;
		return (FALSE);
	}
	if (fd_from == NO_FD_SETTING)
		fd_from = STDOUT_FILENO;
	dup2(fd_to, fd_from);
	close(fd_to);
	return (TRUE);
}

static t_bool
	redirect_out(int fd_from, char *path)
{
	int	fd_to;

	fd_to = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd_to < 0)
	{
		ft_put_cmderror(path, strerror(errno));
		g_status = STATUS_GENERAL_ERR;
		return (FALSE);
	}
	if (fd_from == NO_FD_SETTING)
		fd_from = STDOUT_FILENO;
	dup2(fd_to, fd_from);
	close(fd_to);
	return (TRUE);
}

static t_bool
	redirect_in(int fd_from, char *path)
{
	int	fd_to;

	fd_to = open(path, O_RDONLY);
	if (fd_to < 0)
	{
		ft_put_cmderror(path, strerror(errno));
		g_status = STATUS_GENERAL_ERR;
		return (FALSE);
	}
	if (fd_from == NO_FD_SETTING)
		fd_from = STDIN_FILENO;
	dup2(fd_to, fd_from);
	close(fd_to);
	return (TRUE);
}

static t_bool
	execute_redirection(int fd_from, char *redirect_op, char *path)
{
	if (!(ft_strcmp(redirect_op, APPEND_REDIRECT_OUT)))
		return (append_redirect_out(fd_from, path));
	else if (!(ft_strcmp(redirect_op, REDIRECT_OUT)))
		return (redirect_out(fd_from, path));
	else if (!(ft_strcmp(redirect_op, REDIRECT_IN)))
		return (redirect_in(fd_from, path));
	else
		return (FALSE);
}

t_bool
	ft_set_redirection(t_list *rd)
{
	int		fd_from;
	char	*path;
	char	*redirect_op;
	int		res;

	res = TRUE;
	while (rd && res)
	{
		fd_from = get_fd((char *)(rd->content));
		if (fd_from == OVER_INT_RANGE || FD_MAX < fd_from)
			ft_put_fderror(fd_from);
		redirect_op = get_op((char *)(rd->content));
		path = ft_strdup((char *)(rd->next->content));
		if (fd_from <= TOKEN_ERROR || FD_MAX < fd_from || !redirect_op || !path)
		{
			g_status = STATUS_GENERAL_ERR;
			return (FALSE);
		}
		if (!execute_redirection(fd_from, redirect_op, path))
			res = FALSE;
		ft_free(&redirect_op);
		ft_free(&path);
		rd = rd->next->next;
	}
	return (res);
}
