#include "minishell_sikeda.h"
#include "minishell_tnishina.h"
#include "libft.h"

static char
	*create_new_path(const char *cd_path, const char *path)
{
	char	*ret;
	char	*tmp;

	if (!cd_path || !path)
		return (NULL);
	if (cd_path[ft_strlen(cd_path) - 1] != '/')
	{
		tmp = ft_strjoin(cd_path, "/");
		ret = ft_strjoin(tmp, path);
		if (!tmp || !ret)
		{
			ft_free(&tmp);
			return (NULL);
		}
		ft_free(&tmp);
	}
	else
	{
		ret = ft_strjoin(cd_path, path);
		if (!ret)
			return (NULL);
	}
	return (ret);
}

int
	ft_exec_cd_path(char **path, char **cd_path)
{
	char	**path_arry;
	char	**head;
	char	*original_path;
	int		res;

	if (!*path || !*cd_path)
		return (CD_FAILED);
	original_path = ft_strdup(*path);
	*cd_path = ft_get_pathenv(*cd_path);
	path_arry = ft_split(*cd_path, ':');
	if (!original_path || !*cd_path || !path_arry)
	{
		ft_free(cd_path);
		ft_free(&original_path);
		return (MALLOC_ERR);
	}
	head = path_arry;
	while (*path_arry)
	{
		ft_free(path);
		*path = create_new_path(*path_arry, original_path);
		if (!*path)
		{
			ft_free(&original_path);
			ft_free(cd_path);
			ft_free_split(&head);
			return (MALLOC_ERR);
		}
		if (chdir(*path) == 0)
		{
			if (!ft_strcmp(".", *path_arry))
				res = CD_SUCCESS;
			else
				res = CD_PATH_SUCCESS;
			ft_free(&original_path);
			ft_free(cd_path);
			ft_free_split(&head);
			return (res);
		}
		path_arry++;
	}
	*path = original_path;
	ft_free(cd_path);
	ft_free_split(&head);
	return (CD_PATH_FAILED);
}
