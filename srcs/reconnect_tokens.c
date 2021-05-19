#include "minishell_tnishina.h"
#include "minishell_sikeda.h"
#include "libft.h"

static int
	handle_multi_tokens(t_list *tokens, char *new[3], t_list **args, int *i)
{
	char	*tmp[2];

	ft_memset(tmp, 0, sizeof(tmp));
	tmp[0] = ft_strjoin(new[0], (char *)tokens->content);
	tmp[1] = ft_strjoin((char *)ft_lstlast(tokens)->content, new[2]);
	if (!tmp[0] || !tmp[1])
	{
		ft_free(&new[0]);
		ft_free(&new[1]);
		ft_free(&new[2]);
		ft_free(&tmp[0]);
		ft_lstclear(&tokens, free);
		return (FAILED);
	}
	ft_free((char **)&((*args)->content));
	(*args)->content = tmp[0];
	ft_free((char **)&(ft_lstlast(tokens)->content));
	ft_lstlast(tokens)->content = tmp[1];
	ft_lstlast(tokens)->next = (*args)->next;
	(*args)->next = tokens->next;
	(*args) = ft_lstlast(tokens);
	*i = ft_strlen((char *)(*args)->content);
	ft_lstdelone(tokens, free);
	return (COMPLETED);
}

static int
	handle_single_token(t_list *tokens, char *new[3], t_list **args, int *i)
{
	char	*tmp[2];

	ft_memset(tmp, 0, sizeof(tmp));
	tmp[0] = ft_strjoin(new[0], (char *)tokens->content);
	tmp[1] = ft_strjoin(tmp[0], new[2]);
	if (!tmp[0] || !tmp[1])
	{
		ft_free(&new[0]);
		ft_free(&new[1]);
		ft_free(&new[2]);
		ft_free(&tmp[0]);
		ft_lstclear(&tokens, free);
		return (FAILED);
	}
	ft_free(&tmp[0]);
	ft_free((char **)&((*args)->content));
	(*args)->content = tmp[1];
	*i += ft_strlen((char *)tokens->content);
	ft_lstdelone(tokens, free);
	return (COMPLETED);
}

int
	ft_reconnect_tokens(t_list *t, char *new[3], t_list **args, int *i)
{
	if (ft_lstsize(t) >= 2)
		return (handle_multi_tokens(t, new, args, i));
	else
		return (handle_single_token(t, new, args, i));
}
