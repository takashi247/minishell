#include "minishell_tnishina.h"
#include "minishell_sikeda.h"
#include "libft.h"

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

static void
	set_rd_params(t_list *rd, int *fd_from, char **op, char **path)
{
	*fd_from = get_fd((char *)(rd->content));
	*op = get_op((char *)(rd->content));
	*path = ft_strdup((char *)(rd->next->content));
}

static void
	free_n_update_params(t_list **rd, char **op, char **path)
{
	ft_free(op);
	ft_free(path);
	*rd = (*rd)->next->next;
}

t_bool
	ft_set_redirection(t_list *rd, int std_fds[3])
{
	int		fd_from;
	char	*path;
	char	*redirect_op;
	int		res;
	t_list	*head;

	res = TRUE;
	head = rd;
	while (rd && res)
	{
		set_rd_params(rd, &fd_from, &redirect_op, &path);
		if (!ft_check_param_error(fd_from, path, redirect_op))
			return (FALSE);
		if (!ft_execute_redirection(fd_from, redirect_op, path, std_fds))
			res = FALSE;
		free_n_update_params(&rd, &redirect_op, &path);
	}
	if (res)
		g_status = STATUS_SUCCESS;
	rd = head;
	return (res);
}
