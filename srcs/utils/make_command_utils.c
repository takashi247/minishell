#include "minishell.h"
#include "libft.h"

static void
	delone_command(t_command **command)
{
	if (*command)
	{
		if ((*command)->args)
			ft_lstclear(&((*command)->args), free);
		if ((*command)->redirects)
			ft_lstclear(&((*command)->redirects), free);
		ft_free(&((*command)->op));
		free(*command);
		*command = NULL;
	}
}

void
	ft_clear_commands(t_command **c)
{
	t_command	*prev;
	t_command	*current;

	if (!c)
		return ;
	current = *c;
	while (current)
	{
		prev = current;
		current = current->next;
		delone_command(&prev);
	}
	*c = NULL;
	unlink(HEREDOC_PATH);
}

int
	ft_clear_commands_n_tokens(t_command **c, t_list **t1, t_list **t2)
{
	ft_lstclear(t1, free);
	ft_lstclear(t2, free);
	ft_clear_commands(c);
	g_ms.status = STATUS_GENERAL_ERR;
	return (FAILED);
}

int
	ft_clear_with_syntax_error(t_command **c, t_list **t)
{
	ft_lstclear(t, free);
	ft_clear_commands(c);
	g_ms.status = STATUS_SYNTAX_ERR;
	return (COMPLETED);
}

t_bool
	ft_is_redirect(char *arg)
{
	int		len;

	if (!arg)
		return (FALSE);
	len = ft_strlen(arg);
	if (arg[len - 1] == '>' || arg[len - 1] == '<')
		return (TRUE);
	else
		return (FALSE);
}
