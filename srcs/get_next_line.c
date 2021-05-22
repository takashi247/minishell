#include "minishell_tnishina.h"

void
	ft_free_strs(char **line, char **fd_array)
{
	ft_free(line);
	ft_free(fd_array);
}

static int
	set_line(char **line, char **fd_array, char *find)
{
	int		res;
	char	*tmp;

	res = GNL_SUCCESS;
	if (find)
	{
		tmp = *fd_array;
		*line = ft_substr(*fd_array, 0, find - *fd_array);
		*fd_array = ft_strdup(find + 1);
		if (!(*fd_array))
			res = GNL_ERROR;
		ft_free(&tmp);
	}
	else
	{
		*line = ft_strdup(*fd_array);
		ft_free(fd_array);
		res = GNL_EOF;
	}
	if (!(*line) || res == GNL_ERROR)
	{
		ft_free_strs(line, fd_array);
		res = GNL_ERROR;
	}
	return (res);
}

static void
	read_file(int fd, char **fd_array, char **buff, char **find)
{
	char	*tmp;
	ssize_t	read_count;

	while (1)
	{
		read_count = read(fd, *buff, BUFFER_SIZE);
		if (read_count == EOF || read_count == 0)
			ft_putstr_fd("  \b\b", STDERR_FILENO);
		if (read_count < 0)
			break ;
		(*buff)[read_count] = '\0';
		if (*fd_array)
		{
			tmp = *fd_array;
			*fd_array = ft_strjoin(*fd_array, *buff);
			ft_free(&tmp);
		}
		else
			*fd_array = ft_strdup(*buff);
		*find = ft_strchr(*fd_array, '\n');
		if (*find || !read_count || !*fd_array)
			break ;
	}
}

int
	get_next_line(int fd, char **line)
{
	static char	*fd_array[MAX_FD];
	char		*buff;
	char		*find;

	if (fd < 0 || MAX_FD <= fd)
		return (GNL_ERROR);
	if (line)
		*line = NULL;
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!line || !buff || read(fd, buff, 0) < 0)
	{
		ft_free(&buff);
		ft_free(&fd_array[fd]);
		return (GNL_ERROR);
	}
	find = ft_strchr(fd_array[fd], '\n');
	if (!find)
		read_file(fd, &fd_array[fd], &buff, &find);
	ft_free(&buff);
	if (!fd_array[fd])
		return (GNL_ERROR);
	return (set_line(line, &fd_array[fd], find));
}
