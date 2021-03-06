#include "minishell_sikeda.h"

char
	*ft_getenv(const char *name)
{
	extern char	**environ;
	char		**envptr;
	size_t		len;

	if (!environ || !*name)
		return (NULL);
	len = ft_strlen(name);
	envptr = environ;
	while (*envptr)
	{
		if (!ft_strncmp(name, *envptr, len) && (*envptr)[len] == '=')
			return (ft_strdup(*envptr + len + 1));
		envptr++;
	}
	return (NULL);
}
