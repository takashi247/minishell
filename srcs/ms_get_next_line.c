#include "minishell_tnishina.h"

static t_bool
	erace_input(char *s)
{
	size_t	len;
	char	*b_spaces;

	if (*s)
		len = ft_strlen(s);
	else
		len = 0;
	len += ft_strlen(PROMPT);
	b_spaces = (char *)malloc(sizeof(char) * (len + 1));
	if (!b_spaces)
		return (FALSE);
	ft_memset(b_spaces, '\b', sizeof(char) * (len + 1));
	b_spaces[len] = '\0';
	ft_putstr_fd(b_spaces, STDERR_FILENO);
	ft_free(&b_spaces);
	return (TRUE);
}

static t_bool
	is_end_of_loop(char **line, int *res)
{
	if (!ft_strlen(*line))
	{
		ft_putstr_fd(EXIT_PROMPT, STDERR_FILENO);
		return (TRUE);
	}
	else
	{
		if (!erace_input(*line))
		{
			ft_free(line);
			*res = GNL_ERROR;
			return (TRUE);
		}
		ft_putstr_fd(PROMPT, STDERR_FILENO);
		ft_putstr_fd(*line, STDERR_FILENO);
		return (FALSE);
	}
}

int
	ft_ms_get_next_line(char **line)
{
	char	*tmp[2];
	int		res;

	ft_bzero(tmp, sizeof(tmp));
	while (1)
	{
		res = get_next_line(STDIN_FILENO, &tmp[0]);
		if (res == GNL_ERROR)
		{
			ft_free(&tmp[0]);
			ft_free(&tmp[1]);
			ft_free(line);
			break ;
		}
		tmp[1] = *line;
		*line = ft_strjoin(*line, tmp[0]);
		ft_free(&tmp[0]);
		ft_free(&tmp[1]);
		if (!*line)
			res = GNL_ERROR;
		if (res != GNL_EOF || is_end_of_loop(line, &res))
			break ;
	}
	get_next_line(STDIN_FILENO, NULL);
	return (res);
}
