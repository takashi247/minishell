#include "minishell_sikeda.h"

void
	ft_clear_copied_env(t_list **cpy)
{
	t_list	*tmp;

	if (!cpy)
		return ;
	while (*cpy)
	{
		tmp = (*cpy)->next;
		FREE(*cpy);
		*cpy = tmp;
	}
}

t_list
	*ft_copy_env(void)
{
	t_list	*copy;
	t_list	*envptr;
	t_list	*current;

	copy = NULL;
	envptr = g_env;
	while (envptr)
	{
		current = ft_lstnew(envptr->content);
		if (!current)
		{
			ft_clear_copied_env(&copy);
			return (NULL);
		}
		ft_lstadd_back(&copy, current);
		envptr = envptr->next;
	}
	return (copy);
}
