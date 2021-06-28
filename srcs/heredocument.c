#include "minishell_tnishina.h"

static char
	*get_delimiter(const char *s)
{
	char		*delimiter;
	char		*delimiter_head;
	const char	*ptr;
	size_t		len;

	// TODO: E"'O'"F のようなトークンは E'O'F にする必要があるためこの実装は不十分
	len = 0;
	ptr = s;
	while (*ptr)
		if (*ptr++ != '\'')
			len++;
	delimiter = (char *)malloc(len + 1);
	if (!delimiter)
		return (NULL);
	delimiter_head = delimiter;
	while (*s)
	{
		if (*s != '\'')
			*delimiter++ = *s;
		s++;
	}
	*delimiter = '\0';
	return (delimiter_head);
}

t_bool
	ft_heredoc(t_list *rd)
{
	char	*delimiter;
	char	*line;
	int		no_expand_flg;
	int		fd;

	no_expand_flg = FALSE;
	if (ft_strchr((char *)(rd->next->content), '\'')
		|| ft_strchr((char *)(rd->next->content), '\"'))
		no_expand_flg = TRUE;
	delimiter = get_delimiter((char *)(rd->next->content));
	if (!delimiter)
		return (FALSE);
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
	ft_free(&delimiter);
	return (TRUE);
}
