#include "minishell_tnishina.h"

static void
	free_n_close(char **line, int fd, t_bool should_exit)
{
	if (line)
		ft_free(line);
	close(fd);
	if (should_exit == TRUE)
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
	int		get_res;
	int		write_res;

	get_res = ft_get_line(&line, TRUE);
	write_res = COMPLETED;
	while (write_res != FAILED && 0 < get_res && ft_strcmp(line, delimiter))
	{
		tmp = ft_lstnew(line);
		if (!tmp)
			free_n_close(&line, fd, TRUE);
		write_res = write_heredoc_line(fd, tmp, no_expand_flg);
		ft_lstclear(&tmp, free);
		line = NULL;
		if (write_res != FAILED)
			get_res = ft_get_line(&line, TRUE);
	}
	free_n_close(&line, fd, FALSE);
	if (get_res == GNL_SIGINT)
		return (FAILED);
	if (get_res == GNL_ERROR)
		ft_exit_n_free_g_vars(STATUS_GENERAL_ERR);
	return (write_res);
}

static t_bool
	heredoc(t_list *rd)
{
	char	*delimiter;
	int		no_expand_flg;
	int		fd;

	no_expand_flg = FALSE;
	delimiter = ft_strdup((char *)(rd->next->content));
	if (ft_strchr(delimiter, '\'') || ft_strchr(delimiter, '\"'))
		no_expand_flg = TRUE;
	if (ft_expand_quotation(&delimiter) == FALSE)
	{
		g_ms.status = STATUS_GENERAL_ERR;
		return (ft_free_n_return(&delimiter, FALSE));
	}
	fd = open(HEREDOC_PATH, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
	{
		ft_put_cmderror(HEREDOC_PATH, strerror(errno));
		g_ms.status = STATUS_GENERAL_ERR;
		return (ft_free_n_return(&delimiter, FALSE));
	}
	if (get_n_write_heredoc_line(fd, delimiter, no_expand_flg) == FAILED)
		return (ft_free_n_return(&delimiter, FALSE));
	ft_free(&delimiter);
	return (ft_free_n_return(&delimiter, TRUE));
}

t_bool
	ft_execute_all_heredoc(t_command *command)
{
	t_list	*rd_head;
	t_bool	res;

	ft_sig_prior();
	res = TRUE;
	while (res == TRUE && command)
	{
		rd_head = command->redirects;
		while (res == TRUE && command->redirects)
		{
			if (!ft_strcmp(command->redirects->content, HEREDOC)
				&& !heredoc(command->redirects))
				res = FALSE;
			else
				command->redirects = command->redirects->next->next;
		}
		command->redirects = rd_head;
		command = command->next;
	}
	ft_sig_post();
	return (res);
}
