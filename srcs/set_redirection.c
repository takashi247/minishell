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

static t_bool
	is_redirect(char *str)
{
	if (!ft_strncmp(str, REDIRECT_IN, ft_strlen(REDIRECT_IN))
	|| !ft_strncmp(str, REDIRECT_OUT, ft_strlen(REDIRECT_OUT))
	|| !ft_strncmp(str, APPEND_REDIRECT_OUT, ft_strlen(APPEND_REDIRECT_OUT)))
		return (TRUE);
	else
		return (FALSE);
}

t_bool
	ft_set_redirection(t_list **args)
{
	t_list	*head;
	t_list	*prev;
	int		fd_from;
	int		fd_to;
	char	*path;
	char	*redirect_op;

	prev = NULL;
	head = *args;
	fd_from = -1;
	redirect_op = NULL;
	path = NULL;
	while (*args)
	{
		if (ft_isdigit(((char*)((*args)->content))[0]) && ft_isnumeric((char*)((*args)->content)) && is_redirect((char*)((*args)->next->content)))
		{
			fd_from = ft_atoi((char*)((*args)->content));
			if (fd_from < 0 || FD_MAX < fd_from)
			{
				ft_put_fderror(fd_from);
				g_status = 1;
				return (FALSE);
			}
			redirect_op = ft_strdup((char*)((*args)->next->content));
			path = ft_strdup((char*)((*args)->next->next->content));
			if (!redirect_op || !path)
			{
				FREE(redirect_op);
				FREE(path);
				g_status = 1;
				return (FALSE);
			}
			if (prev)
				prev->next = (*args)->next->next->next;
			else
				head = (*args)->next->next->next;
			ft_lstdelone((*args)->next->next, free);
			ft_lstdelone((*args)->next, free);
			ft_lstdelone((*args), free);
			if (prev)
				*args = prev->next;
			else
				*args = head;
		}
		else if (is_redirect((char*)((*args)->content)))
		{
			redirect_op = ft_strdup((char*)((*args)->content));
			path = ft_strdup((char*)((*args)->next->content));
			if (!redirect_op || !path)
			{
				FREE(redirect_op);
				FREE(path);
				g_status = 1;
				return (FALSE);
			}
			if (prev)
				prev->next = (*args)->next->next;
			else
				head = (*args)->next->next;
			ft_lstdelone((*args)->next, free);
			ft_lstdelone((*args), free);
			if (prev)
				*args = prev->next;
			else
				*args = head;
		}
		if (!redirect_op)
		{
			prev = *args;
			*args = (*args)->next;
		}
		else if (!(ft_strcmp(redirect_op, APPEND_REDIRECT_OUT)))
		{
			fd_to = open(path, O_WRONLY | O_CREAT | O_APPEND, 0666);
			if (fd_to < 0)
			{
				ft_put_cmderror(path, strerror(errno));
				g_status = 1;
				FREE(redirect_op);
				FREE(path);
				return (FALSE);
			}
			if (fd_from == -1)
				fd_from = STDOUT_FILENO;
			dup2(fd_to, fd_from);
			close(fd_to);
		}
		else if (!(ft_strcmp(redirect_op, REDIRECT_OUT)))
		{
			fd_to = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			if (fd_to < 0)
			{
				ft_put_cmderror(path, strerror(errno));
				g_status = 1;
				FREE(redirect_op);
				FREE(path);
				return (FALSE);
			}
			if (fd_from == -1)
				fd_from = STDOUT_FILENO;
			dup2(fd_to, fd_from);
			close(fd_to);
		}
		else if (!(ft_strcmp(redirect_op, REDIRECT_IN)))
		{
			fd_to = open(path, O_RDONLY);
			if (fd_to < 0)
			{
				ft_put_cmderror(path, strerror(errno));
				g_status = 1;
				FREE(redirect_op);
				FREE(path);
				return (FALSE);
			}
			if (fd_from == -1)
				fd_from = STDIN_FILENO;
			dup2(fd_to, fd_from);
			close(fd_to);
		}
		FREE(redirect_op);
		FREE(path);
	}
	*args = head;
	return (TRUE);
}