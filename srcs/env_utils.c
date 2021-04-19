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
		if (!ft_strncmp(name, current, len)
			&& (current[len] == '=' || current[len] == '\0'))
			return (current + len + 1);
		envptr = envptr->next;
	}
	return (NULL);
}

static void
	delone_env(char *str)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(str);
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			str[i] = '\0';
			break ;
		}
		i++;
	}
	if (ft_getenv(str))
		ft_unsetenv(str);
	if (i != len)
		str[i] = '=';
}

int
	ft_setenv(char *str)
{
	t_list	*new;
	char	*cpy;

	if (!g_env || !str || !*str)
		return (UTIL_ERROR);
	delone_env(str);
	cpy = ft_strdup(str);
	if (cpy)
		new = ft_lstnew(cpy);
	if (!cpy || !new)
	{
		if (cpy)
			FREE(cpy);
		return (UTIL_ERROR);
	}
	ft_lstadd_back(&g_env, new);
	return (UTIL_SUCCESS);
}

int
	ft_setenv_sep(const char *name, const char *value)
{
	char	*equal_value;
	char	*env_str;
	int		ret;

	if (!g_env || !name)
		return (UTIL_ERROR);
	equal_value = NULL;
	if (value)
		equal_value = ft_strjoin("=", value);
	if (value && !equal_value)
		return (UTIL_ERROR);
	if (equal_value)
		env_str = ft_strjoin(name, equal_value);
	else
		env_str = ft_strdup(name);
	ret = UTIL_ERROR;
	if (env_str)
		ret = ft_setenv(env_str);
	FREE(equal_value);
	FREE(env_str);
	return (ret);
}

int
	ft_unsetenv(const char *name)
{
	t_list			*envptr;
	t_list			*prev;
	const size_t	len = ft_strlen(name);

	if (!g_env || !name || !*name)
		return (UTIL_ERROR);
	envptr = g_env;
	prev = NULL;
	while (envptr)
	{
		if (!ft_strncmp(name, envptr->content, len)
			&& (((char*)envptr->content)[len] == '='
			|| ((char*)envptr->content)[len] == '\0'))
		{
			if (prev)
				prev->next = envptr->next;
			else
				g_env = envptr->next;
			ft_lstdelone(envptr, free);
			return (UTIL_SUCCESS);
		}
		prev = envptr;
		envptr = envptr->next;
	}
	return (UTIL_ERROR);
}
