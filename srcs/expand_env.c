#include "minishell_tnishina.h"
#include "libft.h"

static t_bool
	create_empty_lst(t_list **tokens, t_list **head)
{
	char	*str;

	str = ft_strdup("");
	if (!str)
	{
		g_ms.status = STATUS_GENERAL_ERR;
		ft_lstdelone(*tokens, free);
		return (FALSE);
	}
	*head = ft_lstnew(str);
	ft_lstdelone(*tokens, free);
	*tokens = (*head)->next;
	return (TRUE);
}

static t_bool
	delete_env(t_list **tokens, t_list **head, t_list *prev, int res)
{
	if (!prev)
	{
		if (res == TOKEN_DELETED || (*tokens)->next)
		{
			*head = (*tokens)->next;
			ft_lstdelone(*tokens, free);
			*tokens = *head;
		}
		else if (!create_empty_lst(tokens, head))
			return (FALSE);
	}
	else
	{
		prev->next = (*tokens)->next;
		ft_lstdelone(*tokens, free);
		*tokens = prev->next;
	}
	return (TRUE);
}

/*
** l[0]: previous entry in the list
** l[1]: current entry in the list
*/

static int
	handle_non_complete(t_list *l[2], char **pre_expand, int res, t_list **head)
{
	if (res == FAILED)
	{
		ft_free(pre_expand);
		return (FAILED);
	}
	else if (l[0] && ft_is_redirect((char *)l[0]->content))
	{
		ft_put_cmderror(*pre_expand, AMBIGUOUS_REDIRECT_ERR_MSG);
		g_ms.status = STATUS_GENERAL_ERR;
		ft_free(pre_expand);
		return (REDIRECT_DELETED);
	}
	else if (!delete_env(&l[1], head, l[0], res))
	{
		ft_free(pre_expand);
		return (FAILED);
	}
	ft_free(pre_expand);
	return (COMPLETED);
}

/*
** lists[0]: previous entry in the list
** lists[1]: current entry in the list
*/

static int
	expand_list(t_list **head)
{
	t_list	*lists[2];
	char	*pre_expand;
	int		res;

	if (!(*head))
		return (COMPLETED);
	lists[0] = NULL;
	lists[1] = *head;
	res = COMPLETED;
	while (lists[1] && res != FAILED && res != REDIRECT_DELETED)
	{
		pre_expand = ft_strdup((char *)lists[1]->content);
		res = ft_find_n_replace_env(&lists[1]);
		if (res == COMPLETED)
		{
			lists[0] = lists[1];
			lists[1] = lists[1]->next;
			ft_free(&pre_expand);
		}
		else
			res = handle_non_complete(lists, &pre_expand, res, head);
	}
	return (res);
}

int
	ft_expand_env_var(t_command *c)
{
	int	exp_args_res;
	int	exp_redirect_res;

	if (!c || c->expanded)
		return (COMPLETED);
	else
	{
		exp_args_res = COMPLETED;
		exp_redirect_res = COMPLETED;
		if (c->args)
			exp_args_res = expand_list(&(c->args));
		if (c->redirects)
			exp_redirect_res = expand_list(&(c->redirects));
		if (exp_args_res == FAILED
			|| exp_redirect_res == FAILED)
			return (FAILED);
		else if (exp_redirect_res == REDIRECT_DELETED)
			return (REDIRECT_DELETED);
		c->expanded = TRUE;
		return (COMPLETED);
	}
}
