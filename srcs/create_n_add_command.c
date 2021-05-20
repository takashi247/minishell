#include "minishell_tnishina.h"

t_command
	*ft_get_last_command(t_command *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

void
	ft_add_command(t_command **head, t_command *new)
{
	t_command	*tmp;

	if (!head || !new)
		return ;
	if (!*head)
		*head = new;
	else
	{
		tmp = ft_get_last_command(*head);
		tmp->next = new;
	}
}

t_bool
	ft_is_operator(char c)
{
	if (c == '|' || c == ';' || c == '\0')
		return (TRUE);
	else
		return (FALSE);
}

static t_command
	*set_args_and_op(t_command *command, t_list *tokens)
{
	t_list	*head;
	t_list	*prev;

	head = tokens;
	prev = NULL;
	while (tokens && !(ft_is_operator(((char *)tokens->content)[0])))
	{
		prev = tokens;
		tokens = tokens->next;
	}
	if (prev)
	{
		prev->next = NULL;
		command->args = head;
	}
	if (tokens)
		command->op = ft_strdup((char *)tokens->content);
	else
		command->op = ft_strdup(NEWLINE);
	if (!(command->op))
		return (NULL);
	ft_lstclear(&tokens, free);
	return (command);
}

t_command
	*ft_create_command(t_list *token_head)
{
	t_command	*new_command;

	if (!token_head)
		return (NULL);
	new_command = (t_command *)malloc(sizeof(t_command));
	if (!new_command)
		return (NULL);
	ft_bzero(new_command, sizeof(t_command));
	return (set_args_and_op(new_command, token_head));
}
