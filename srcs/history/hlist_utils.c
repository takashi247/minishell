#include "minishell.h"

static t_history
	*new_history(const char *line, const size_t len,
		t_history *prev, t_history *next)
{
	t_history	*new;

	new = (t_history *)malloc(sizeof(t_history));
	if (!new)
		return (NULL);
	if (len == SIZE_MAX)
		return (NULL);
	new->line = (char *)malloc((len + 1) * sizeof(char));
	if (!new->line)
	{
		free(new);
		return (NULL);
	}
	ft_strlcpy(new->line, line, len + 1);
	new->len = len;
	new->prev = prev;
	new->next = next;
	return (new);
}

int
	ft_add_history(t_history_list *hlist, const char *line, const size_t len)
{
	t_history	*new;

	if (!hlist->last)
		new = new_history(line, len, NULL, NULL);
	else
		new = new_history(line, len, hlist->last, NULL);
	if (!new)
		return (UTIL_ERROR);
	if (!hlist->last)
		hlist->last = new;
	else
		hlist->last->next = new;
	hlist->last = new;
	return (UTIL_SUCCESS);
}

void
	ft_delone_history(t_history *node)
{
	if (!node)
		return ;
	free(node->line);
	free(node);
}

void
	ft_clear_history(t_history **node_ptr)
{
	t_history	*node;
	t_history	*target;

	if (!node_ptr)
		return ;
	node = *node_ptr;
	while (node && node->prev)
		node = node->prev;
	while (node)
	{
		target = node;
		node = node->next;
		ft_delone_history(target);
	}
	*node_ptr = NULL;
}
