#include "minishell_sikeda.h"

char
	*ft_getenv(const char *name)
{
	t_list	*envptr;
	size_t	len;
	char	*current;

	if (!g_env || !*name)
		return (NULL);
	len = ft_strlen(name);
	envptr = g_env;
	while (envptr)
	{
		current = envptr->content;
		if (!ft_strncmp(name, current, len) && current[len] == '=')
			return (ft_strdup(current + len + 1));
		envptr = envptr->next;
	}
	return (NULL);
}
