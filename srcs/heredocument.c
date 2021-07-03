#include "minishell_tnishina.h"

static void
	close_n_exit(int fd)
{
	close(fd);
	ft_exit_n_free_g_vars(STATUS_GENERAL_ERR);
}

static int
	write_heredoc_line(int fd, t_list *tmp, int no_expand_flg)
{
	int	res;

	res = COMPLETED;
	if (no_expand_flg == FALSE)
		res = ft_expand_env_for_heredoc(&tmp);
	if (res != FAILED)
		ft_putendl_fd(tmp->content, fd);
	return (res);
}

static int
	get_n_write_heredoc_line(int fd, const char *delimiter, int no_expand_flg)
{
	char	*line;
	t_list	*tmp;
	int		res;

	if (ft_get_line(&line, TRUE) == GNL_ERROR)
		close_n_exit(fd);
	res = COMPLETED;
	while (res != FAILED && ft_strcmp(line, delimiter))
	{
		tmp = ft_lstnew(line);
		if (!tmp)
		{
			ft_free(&line);
			close_n_exit(fd);
		}
		res = write_heredoc_line(fd, tmp, no_expand_flg);
		ft_lstclear(&tmp, free);
		if (res != FAILED && ft_get_line(&line, TRUE) == GNL_ERROR)
			close_n_exit(fd);
	}
	ft_free(&line);
	close(fd);
	return (res);
}

static t_bool
	heredoc(t_list *rd)
{
	char	*delimiter;
	int		no_expand_flg;
	int		fd;

	no_expand_flg = FALSE;
	delimiter = (char *)(rd->next->content);
	if (ft_strchr(delimiter, '\'') || ft_strchr(delimiter, '\"'))
		no_expand_flg = TRUE;
	if (ft_expand_quotation(&delimiter) == FALSE)
	{
		g_ms.status = STATUS_GENERAL_ERR;
		return (FALSE);
	}
	fd = open(HEREDOC_PATH, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
	{
		ft_put_cmderror(HEREDOC_PATH, strerror(errno));
		g_ms.status = STATUS_GENERAL_ERR;
		return (FALSE);
	}
	if (get_n_write_heredoc_line(fd, delimiter, no_expand_flg) == FAILED)
		return (FALSE);
	return (TRUE);
}

t_bool
	ft_execute_all_heredoc(t_list *rd)
{
	while (rd)
	{
		if (!ft_strcmp(rd->content, HEREDOC) && !heredoc(rd))
			return (FALSE);
		rd = rd->next->next;
	}
	return (TRUE);
}
