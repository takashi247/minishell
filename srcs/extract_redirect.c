#include "minishell_sikeda.h"
#include "minishell_tnishina.h"
#include "libft.h"

static void
	update_redirects(t_command *c, t_list **current, t_list *prev)
{
	if (prev)
		prev->next = (*current)->next->next;
	else
		c->args = (*current)->next->next;
	(*current)->next->next = NULL;
	ft_lstadd_back(&(c->redirects), *current);
	if (prev)
		(*current) = prev->next;
	else
		(*current) = c->args;
}

void
	ft_extract_redirect(t_command *c)
{
	t_list	*current;
	t_list	*prev;

	while (c)
	{
		current = c->args;
		prev = NULL;
		while (current)
		{
			if (ft_is_redirect((char *)(current->content)))
				update_redirects(c, &current, prev);
			else
			{
				prev = current;
				current = current->next;
			}
		}
		c = c->next;
	}
}