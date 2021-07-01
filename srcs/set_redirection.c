#include "minishell_tnishina.h"

void
	ft_free_n_update_params(t_list **rd, char **op, char **path)
{
	ft_free(op);
	ft_free(path);
	if (rd)
		*rd = (*rd)->next->next;
}

t_bool
	ft_set_redirection(t_list *rd, int std_fds[3])
{
	int		fd_from;
	char	*path;
	char	*redirect_op;
	t_bool	res;
	t_list	*head;

	res = TRUE;
	head = rd;
	while (rd && res)
	{
		if (!ft_strcmp(rd->content, HEREDOC))
		{
			if (!ft_heredoc(rd) || !ft_set_rd_params_for_heredoc(
					rd, &fd_from, &redirect_op, &path))
				return (FALSE);
		}
		else if (!ft_set_rd_params(rd, &fd_from, &redirect_op, &path))
			return (FALSE);
		if (!ft_check_param_error(fd_from, path, redirect_op))
			return (FALSE);
		if (!ft_execute_redirection(fd_from, redirect_op, path, std_fds))
			res = FALSE;
		ft_free_n_update_params(&rd, &redirect_op, &path);
	}
	if (res)
		g_ms.status = STATUS_SUCCESS;
	rd = head;
	return (res);
}
