#include "minishell_tnishina.h"
#include "libft.h"

void
	ft_free_str(char **str)
{
	free(*str);
	*str = NULL;
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
		if (!(*fd_array = ft_strdup(find + 1)))
			res = GNL_ERROR;
		ft_free_str(&tmp);
	}
	else
	{
		*line = ft_strdup(*fd_array);
		ft_free_str(fd_array);
		res = GNL_EOF;
	}
	if (!(*line) || res == GNL_ERROR)
	{
		ft_free_str(line);
		ft_free_str(fd_array);
		res = GNL_ERROR;
	}
	return (res);
}

static void
	read_file(int fd, char **fd_array, char **buff, char **find)
{
	char	*tmp;
	ssize_t	read_count;

	while ((read_count = read(fd, *buff, BUFFER_SIZE)) >= 0)
	{
		(*buff)[read_count] = '\0';
		if (*fd_array)
		{
			tmp = *fd_array;
			*fd_array = ft_strjoin(*fd_array, *buff);
			ft_free_str(&tmp);
		}
		else
			*fd_array = ft_strdup(*buff);
		if ((*find = ft_strchr(*fd_array, '\n')) || !read_count || !*fd_array)
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
		ft_free_str(&buff);
		ft_free_str(&fd_array[fd]);
		return (GNL_ERROR);
	}
	if (!(find = ft_strchr(fd_array[fd], '\n')))
		read_file(fd, &fd_array[fd], &buff, &find);
	ft_free_str(&buff);
	if (!fd_array[fd])
		return (GNL_ERROR);
	return (set_line(line, &fd_array[fd], find));
}
