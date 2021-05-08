#include "minishell_sikeda.h"

void
	ft_lstdelend(t_list **lst, void (*del)(void*))
{
	t_list	*prev;
	t_list	*current;

	if (!lst || !del)
		return ;
	current = *lst;
	prev = NULL;
	while (current && current->next)
	{
		prev = current;
		current = current->next;
	}
	ft_lstdelone(current, del);
	if (prev)
		prev->next = NULL;
	else
		*lst = NULL;
}

int
	ft_lstnew_and_lstadd_back(t_list **path_list, const char *str)
{
	t_list	*new;
	char	*tmp;

	new = NULL;
	tmp = ft_strdup(str);
	if (tmp)
		new = ft_lstnew(tmp);
	if (!tmp || !new)
	{
		ft_free(&tmp);
		ft_lstclear(path_list, free);
		return (UTIL_ERROR);
	}
	ft_lstadd_back(path_list, new);
	return (UTIL_SUCCESS);
}
