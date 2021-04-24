#include "minishell_sikeda.h"

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
