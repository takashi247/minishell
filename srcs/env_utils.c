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

int
	ft_unsetenv(const char *name)
{
	t_list	*envptr;
	t_list	*prev;
	size_t	len;

	if (!g_env || !name || !*name)
		return (ENVUTIL_ERROR);
	envptr = g_env;
	prev = NULL;
	len = ft_strlen(name);
	while (envptr)
	{
		if (!ft_strncmp(name, envptr->content, len)
		&& ((char*)envptr->content)[len] == '=')
		{
			if (prev)
				prev->next = envptr->next;
			else
				g_env = envptr->next;
			ft_lstdelone(envptr, free);
			return (ENVUTIL_SUCCESS);
		}
		prev = envptr;
		envptr = envptr->next;
	}
	return (ENVUTIL_ERROR);
}
