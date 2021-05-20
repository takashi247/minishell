#include "minishell_tnishina.h"
#include "libft.h"

static char
	*convert_env(char *new[3])
{
	char	*env;

	if (!ft_strcmp(new[1], "\?"))
		env = ft_itoa(g_ms.status);
	else
	{
		if ((ft_getenv(new[1])))
			env = ft_strdup(ft_getenv(new[1]));
		else
			env = ft_strdup("");
	}
	if (!env)
	{
		ft_free(&new[0]);
		ft_free(&new[1]);
		ft_free(&new[2]);
		return (NULL);
	}
	return (env);
}

static int
	reconnect_deleted_token(char *new[3], t_list **args)
{
	ft_free((char **)&((*args)->content));
	(*args)->content = ft_strjoin(new[0], new[2]);
	if (!((*args)->content))
	{
		ft_free(&new[0]);
		ft_free(&new[1]);
		ft_free(&new[2]);
		return (FAILED);
	}
	if (ft_strlen((char *)(*args)->content))
		return (COMPLETED);
	else
		return (TOKEN_DELETED);
}

int
	ft_replace_env_token(t_list **args, int *env_pos, int *i)
{
	t_list	*tokens;
	char	*new[3];
	int		res;
	char	*env;

	tokens = NULL;
	ft_memset(new, 0, sizeof(new));
	if (!ft_create_new_strs((char *)(*args)->content, env_pos, new))
		return (FAILED);
	env = convert_env(new);
	if (!env)
		return (FAILED);
	if (ft_make_token(&tokens, env, ft_is_space) == FAILED)
	{
		ft_lstclear(&tokens, free);
		ft_free_all_chars(&env, NULL, new);
		return (FAILED);
	}
	if (tokens)
		res = ft_reconnect_tokens(tokens, new, args, i);
	else
		res = reconnect_deleted_token(new, args);
	ft_free_all_chars(&env, NULL, new);
	return (res);
}
