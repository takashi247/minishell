#include "minishell.h"

static int
	get_fd(char *arg)
{
	int		len;
	char	*fd_str;
	int		fd_num;

	if (!arg)
		return (GENERAL_ERROR);
	len = ft_strlen(arg);
	if (len == 1 || arg[0] == '>' || arg[0] == '<')
		return (NO_FD_SETTING);
	else
	{
		if (ft_isdigit(arg[len - 2]))
			fd_str = ft_substr(arg, 0, len - 1);
		else
			fd_str = ft_substr(arg, 0, len - 2);
		if (!fd_str)
			fd_num = GENERAL_ERROR;
		else if (ft_isover_intrange(fd_str))
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

t_bool
	ft_set_rd_params_for_heredoc(
		t_list *rd, int *fd_from, char **op, char **path)
{
	*fd_from = get_fd((char *)(rd->content));
	*op = get_op((char *)(rd->content));
	*path = ft_strdup(HEREDOC_PATH);
	if (!*op || !*path || ft_strcmp(*op, HEREDOC))
	{
		g_ms.status = STATUS_GENERAL_ERR;
		ft_free(op);
		ft_free(path);
		return (FALSE);
	}
	return (TRUE);
}

t_bool
	ft_set_rd_params(t_list *rd, int *fd_from, char **op, char **path)
{
	char	*pre_expand;
	int		res;

	*fd_from = get_fd((char *)(rd->content));
	*op = get_op((char *)(rd->content));
	pre_expand = ft_strdup((char *)(rd->next->content));
	if (!*op || !pre_expand)
	{
		g_ms.status = STATUS_GENERAL_ERR;
		ft_free(op);
		return (FALSE);
	}
	res = ft_find_n_replace_env(&rd->next, TRUE);
	if (res == FAILED)
	{
		ft_free_n_update_params(NULL, op, &pre_expand);
		g_ms.status = STATUS_GENERAL_ERR;
		return (FALSE);
	}
	if (!ft_validate_path(rd, path, pre_expand, res))
	{
		ft_free(op);
		return (FALSE);
	}
	return (TRUE);
}
