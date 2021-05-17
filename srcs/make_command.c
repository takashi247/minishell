#include "minishell_tnishina.h"
#include "minishell_sikeda.h"
#include "libft.h"

static t_bool
	is_valid_rediret(t_command *c, t_list *current)
{
	if (ft_is_redirect((char *)(current->content)))
	{
		if (!(current->next))
		{
			ft_put_syntaxerror_with_token(c->op);
			return (FALSE);
		}
		else if (ft_is_redirect((char *)(current->next->content)))
		{
			ft_put_syntaxerror_with_token((char *)(current->next->content));
			return (FALSE);
		}
	}
	return (TRUE);
}

static t_bool
	is_valid_command(t_command *c)
{
	t_list	*current;

	if ((!(ft_strcmp(c->op, "|")) && !(c->args))
		|| (!(ft_strcmp(c->op, ";")) && !(c->args)))
	{
		ft_put_syntaxerror_with_token(c->op);
		return (FALSE);
	}
	current = c->args;
	while (current)
	{
		if (!is_valid_rediret(c, current))
			return (FALSE);
		current = current->next;
	}
	return (TRUE);
}

static t_bool
	is_valid_pipe(t_command *c)
{
	while (c)
	{
		if (!(ft_strcmp(c->op, "|")) && !(c->next))
		{
			ft_put_cmderror(c->op, MULTILINE_ERROR_MSG);
			return (FALSE);
		}
		c = c->next;
	}
	return (TRUE);
}

int
	ft_make_command(t_command **commands, t_list *tokens)
{
	t_list		*head;
	t_list		*tmp;
	t_command	*new_command;

	*commands = NULL;
	while (tokens)
	{
		head = tokens;
		while (!(ft_is_operator(((char *)tokens->content)[0])) && tokens->next)
			tokens = tokens->next;
		tmp = tokens->next;
		tokens->next = NULL;
		new_command = ft_create_command(head);
		if (!new_command)
			return (ft_clear_commands_n_tokens(commands, &head, &tmp));
		ft_add_command(commands, new_command);
		if (!(is_valid_command(ft_get_last_command(*commands))))
			return (ft_clear_with_syntax_error(commands, &tmp));
		ft_extract_redirect(*commands);
		tokens = tmp;
	}
	if (!(is_valid_pipe(*commands)))
		return (ft_clear_with_syntax_error(commands, NULL));
	return (COMPLETED);
}
