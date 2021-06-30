#include "minishell_tnishina.h"

t_bool
	ft_heredoc(t_list *rd)
{
	char	*delimiter;
	char	*line;
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
	while (1)
	{
		if (ft_get_line(&line, TRUE) == GNL_ERROR)
			ft_exit_n_free_g_vars(STATUS_GENERAL_ERR);
		if (!ft_strcmp(line, delimiter))
		{
			ft_free(&line);
			break ;
		}
		// if (no_expand_flg == FALSE)
			// TODO: 変数展開
		write(fd, line, ft_strlen(line));
		ft_free(&line);
		write(fd, "\n", 1);
	}
	close(fd);
	return (TRUE);
}
