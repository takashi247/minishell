#include "minishell_tnishina.h"

void
	ft_free_all_chars(char **env, char *tmp[2], char *new[3])
{
	if (env)
		ft_free(env);
	if (tmp)
	{
		ft_free(&tmp[0]);
		ft_free(&tmp[1]);
		ft_free(&tmp[2]);
	}
	if (new)
	{
		ft_free(&new[0]);
		ft_free(&new[1]);
		ft_free(&new[2]);
	}
}

t_bool
	ft_create_new_strs(char *content, int *env_pos, char *new[3])
{
	int	p[2];

	if (content[env_pos[0] + 1] != '{')
		p[0] = env_pos[0] + 1;
	else
		p[0] = env_pos[0] + 2;
	if (content[env_pos[0] + 1] == '{' && content[env_pos[1]] == '}')
		p[1] = env_pos[1] + 1;
	else
		p[1] = env_pos[1];
	new[0] = ft_substr(content, 0, env_pos[0]);
	new[1] = ft_substr(content, p[0], env_pos[1] - p[0]);
	new[2] = ft_strdup(content + p[1]);
	if (!new[0] || !new[1] || !new[2])
	{
		ft_free(&new[0]);
		ft_free(&new[1]);
		return (FALSE);
	}
	return (TRUE);
}

static t_bool
	combine_strs(char **content, char *new[3], char *tmp[3], int *i)
{
	tmp[0] = *content;
	if (!ft_strcmp(new[1], "\?"))
		tmp[1] = ft_itoa(g_ms.status);
	else if (ft_getenv(new[1]))
		tmp[1] = ft_strdup(ft_getenv(new[1]));
	else
		tmp[1] = ft_strdup("");
	tmp[2] = ft_strjoin(new[0], tmp[1]);
	*content = ft_strjoin(tmp[2], new[2]);
	if (!tmp[1] || !tmp[2] || !(*content))
	{
		ft_free_all_chars(NULL, tmp, new);
		return (FALSE);
	}
	*i += ft_strlen(tmp[1]);
	return (TRUE);
}

int
	ft_replace_q_env(char **content, int *env_pos, int *i)
{
	char	*new[3];
	char	*tmp[3];
	int		res;

	ft_memset(new, 0, sizeof(new));
	ft_memset(tmp, 0, sizeof(tmp));
	if (!ft_create_new_strs(*content, env_pos, new))
		return (FAILED);
	if (!combine_strs(content, new, tmp, i))
		return (FAILED);
	if (!(*content) || !ft_strlen(*content))
		res = ENV_DELETED;
	else
		res = COMPLETED;
	ft_free_all_chars(NULL, tmp, new);
	return (res);
}
