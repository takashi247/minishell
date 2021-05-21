#include "minishell_tnishina.h"

char
	*ft_join_path(const char *path, const char *new)
{
	char	*tmp;
	char	*result;

	if (!path || !new)
		return (NULL);
	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, new);
	free(tmp);
	return (result);
}

char
	*ft_get_home_path(const char *args)
{
	char	*path;

	if (!args)
	{
		path = ft_getenv("HOME");
		if (!path)
		{
			ft_put_cmderror("cd", "HOME not set");
			return (NULL);
		}
		if (*path == '\0')
			return ("");
		return (path);
	}
	return ((char *)args);
}
