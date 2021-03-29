#include "minishell_tnishina.h"
#include "minishell_sikeda.h"
#include "libft.h"

/* コメントアウトしている部分は一旦無視してください

t_bool
	is_operator(char *elem)
{
	if (!(ft_strcmp(elem, "&")) || !(ft_strcmp(elem, "&&")) ||
		!(ft_strcmp(elem, "|")) || !(ft_strcmp(elem, "||")) ||
		!(ft_strcmp(elem, ";")))
		return (TRUE);
	else
		return (FALSE);
}

t_bool
	is_end_of_command(char *elem)
{
	if (elem[ft_strlen(elem) - 1] == ';' ||
		elem == NULL)
		return (TRUE);
	else
		return (FALSE);
}

t_command
	*ft_create_command(char **elem_head, int argc)
{
	t_command	*new_command;

	if (!(new_command = (t_command *)malloc(sizeof(t_command))))
		return (NULL);
	ft_memset(new_command, 0, sizeof(t_command));
	new_command->argv = elem_head;
	new_command->argc = argc;
	if (is_operator(*(elem_head + argc - 1)))
		new_command->op = *(elem_head + argc - 1);
	else if(!(new_command->op = ft_strdup(";")))
		return (NULL);
	return (new_command);
}

t_command
	*ft_get_last_command(t_command *command_head)
{
	if (!command_head)
		return (NULL);
	while (command_head->next)
		command_head = command_head->next;
	return (command_head);
}

t_bool
	ft_add_command(t_command **command_head, t_command *new_command)
{
	t_command	*last_command;

	if (!command_head || !new_command)
		return (FALSE);
	if (!(*command_head))
		*command_head = new_command;
	else
	{
		last_command = ft_get_last_command(*command_head);
		last_command->next = new_command;
	}
	return (TRUE);
}

void
	ft_clear_command(t_command **command_head)
{
	t_command	*prev;
	t_command	*current;

	if (!command_head)
		return ;
	current = *command_head;
	while (current)
	{
		prev = current;
		current = current->next;
		FREE(prev);
	}
	FREE(*command_head);
}

t_bool
	ft_load_command(char **elems, t_command **command_head)
{
	int		argc;
	char	**elem_head;

	while (TRUE)
	{
		argc = 0;
		elem_head = elems;
		while (!(is_operator(*(elems + argc))) ||
			is_end_of_command(*(elems + argc)))
			argc++;
		argc++;
		if (!(ft_add_command(command_head, 
			ft_create_command(elem_head, argc))))
		{
			ft_clear_command(command_head);
			return (FALSE);
		}
		if (*(elems + argc - 1) == NULL)
			break;
		else
			elems += argc;
	}
	return (TRUE);
}

static t_bool
	is_valid_quote(char **line)
{
	if (**line == '\"')
	{
		(*line)++;
		while (**line && **line != '\"')
			(*line)++;
	}
	else if (**line == '\'')
	{
		(*line)++;
		while (**line && **line != '\'')
			(*line)++;
	}
	if (**line == '\0')
		return (FALSE);
	(*line)++;
	return (TRUE);
}

static int
	count_elems(char *line)
{
	int	num_elems;

	num_elems = 0;
	while (*line)
	{
		if (*line == '\'' || *line == '\"')
		{
			if (!(is_valid_quote(&line)))
				return (-1);
			num_elems++;
		}
		while (!(is_delimiter(*line)))
			line++;
		num_elems++;
		while (*line == ' ')
			line++;
		if (*line == '\0')
			return (num_elems);
		if (!(is_valid_delimiter(&line)))
			return (-1);
		num_elems++;
	}
	return (num_elems);
}

*/

static t_bool
	is_delimiter(char c)
{
	if (c == ' ' || c == '|' || c == '&' || c == ';' ||
		c == '<' || c == '>' || c == '\0')
		return (TRUE);
	else
		return (FALSE);
}

static t_list
	*exit_with_error(t_list **tokens, char **cpy)
{
	FREE(*cpy);
	ft_lstclear(tokens, free);
	return (NULL);
}

t_list
	*ft_make_token(char *line)
{
	t_list	*tokens;
	t_list	*new;
	int		i;
	char	*cpy;

	if (!line)
		return (NULL);
	tokens = NULL;
	while (*line)
	{
		i = 0;
		while (*line == ' ')
			line++;
		while (!(is_delimiter(line[i])))
			i++;
		if (!(cpy = i != 0 ? ft_substr(line, 0, i) : 
			ft_substr(line, 0, i + 1)) || !(new = ft_lstnew(cpy)))
			return (exit_with_error(&tokens, &cpy));
		ft_lstadd_back(&tokens, new);
		line = line[i] ? line + i + (i == 0) : line + i;
	}
	return (tokens);
}

#ifdef TOKENTEST
int
	main(int ac, char **av)
{
	char		*line;
	extern char	**environ;
	t_list		*tokens;
	t_list		*head;

	if (ac == 1)
	{
		ft_putstr_fd(PROMPT, STDOUT_FILENO);
		while (get_next_line(STDIN_FILENO, &line) == 1 &&
			(ft_strncmp(line, "exit", 5)) &&
			(tokens = ft_make_token(line)))
		{
			head = tokens;
			while (tokens)
			{
				ft_putstr_fd("[", STDOUT_FILENO);
				ft_putstr_fd(tokens->content, STDOUT_FILENO);
				ft_putstr_fd("]\n", STDOUT_FILENO);
				tokens = tokens->next;
			}
			FREE(line);
			ft_lstclear(&head, free);
			ft_putstr_fd(PROMPT, STDOUT_FILENO);
		}
		FREE(line);
		get_next_line(STDIN_FILENO, NULL);
		ft_putstr_fd(EXIT_PROMPT, STDOUT_FILENO);
	}
	else
	{
		if ((tokens = ft_make_token(av[1])))
		{
			head = tokens;
			while (tokens)
			{
				ft_putstr_fd("[", STDOUT_FILENO);
				ft_putstr_fd(tokens->content, STDOUT_FILENO);
				ft_putstr_fd("]\n", STDOUT_FILENO);
				tokens = tokens->next;
			}
			ft_lstclear(&head, free);
		}
	}
	exit(0);
}
#endif
