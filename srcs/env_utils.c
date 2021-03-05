#include "minishell_sikeda.h"

char
	*get_env_by_key(char *key, char **environ)
{
	size_t	len;

	if (!environ)
		return (NULL);
	len = ft_strlen(key);
	while (*environ)
	{
		if (!ft_strncmp(key, *environ, len) && (*environ)[len] == '=')
			return (ft_strdup(*environ + len + 1));
		environ++;
	}
	return (NULL);
}
