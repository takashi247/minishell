#include "minishell_tnishina.h"
#include "minishell_sikeda.h"
#include "libft.h"

static void
	add_pwd_front(char **path_env)
{
	char	*tmp;

	tmp = *path_env;
	*path_env = ft_strjoin(".", *path_env);
	if (!(*path_env))
		ft_exit_n_free_g_vars(STATUS_GENERAL_ERR);
	ft_free(&tmp);
}

static void
	add_pwd_middle(char **path_env, int i)
{
	char	*tmp;
	char	*front;
	char	*back;

	tmp = *path_env;
	front = ft_substr(*path_env, 0, i + 1);
	back = ft_strdup(*path_env + i + 1);
	ft_free(&tmp);
	tmp = ft_strjoin(front, ".");
	*path_env = ft_strjoin(tmp, back);
	if (!front || !back || !tmp || !(*path_env))
		ft_exit_n_free_g_vars(STATUS_GENERAL_ERR);
	ft_free(&front);
	ft_free(&back);
	ft_free(&tmp);
}

static void
	add_pwd_back(char **path_env)
{
	char	*tmp;

	tmp = *path_env;
	*path_env = ft_strjoin(*path_env, ".");
	if (!(*path_env))
		ft_exit_n_free_g_vars(STATUS_GENERAL_ERR);
	ft_free(&tmp);
}

char
	*ft_get_pathenv(char *s)
{
	int		i;
	char	*path_env;

	if (!s)
		return (NULL);
	path_env = ft_strdup(s);
	if (!path_env)
		ft_exit_n_free_g_vars(STATUS_GENERAL_ERR);
	i = 0;
	while (path_env[i])
	{
		if (!i && path_env[i] == ':')
			add_pwd_front(&path_env);
		else if (path_env[i] == ':' && path_env[i + 1] == ':')
			add_pwd_middle(&path_env, i);
		else if (path_env[i] == ':' && !path_env[i + 1])
			add_pwd_back(&path_env);
		i++;
	}
	return (path_env);
}
