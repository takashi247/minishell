#include "minishell_tnishina.h"
#include "minishell_sikeda.h"
#include "libft.h"

t_bool
	ft_is_operator(char c)
{
	if (c == '|' || c == ';' || c == '\0')
		return (TRUE);
	else
		return (FALSE);
}

static void
	delone_command(t_command *command)
{
	if (command)
	{
		if (command->args)
			ft_lstclear(&(command->args), free);
		FREE(command->op);
		FREE(command);
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
		delone_command(prev);
	}
	*c = NULL;
}

static int
	clear_commands_and_tokens(t_command **c, t_list **t1, t_list **t2)
{
	ft_lstclear(t1, free);
	ft_lstclear(t2, free);
	ft_clear_commands(c);
	g_status = STATUS_GENERAL_ERR;
	return (FAILED);
}

static int
	clear_with_syntax_error(t_command **c, t_list **t1, t_list **t2)
{
	ft_lstclear(t1, free);
	ft_lstclear(t2, free);
	ft_clear_commands(c);
	g_status = STATUS_SYNTAX_ERR;
	return (COMPLETED);
}

static t_command
	*get_last_command(t_command *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

static void
	add_command(t_command **head, t_command *new)
{
	t_command	*tmp;

	if (!head || !new)
		return ;
	if (!*head)
		*head = new;
	else
	{
		tmp = get_last_command(*head);
		tmp->next = new;
	}
}

static t_command
	*set_args_and_op(t_command *command, t_list *tokens)
{
	t_list	*head;
	t_list	*prev;
	char	*op;

	head = tokens;
	prev = NULL;
	while (tokens && !(ft_is_operator(((char*)tokens->content)[0])))
	{
		prev = tokens;
		tokens = tokens->next;
	}
	if (prev)
		prev->next = NULL;
	command->args = prev ? head : NULL;
	op = !tokens ? "newline" : (char*)tokens->content;
	if (!(command->op = ft_strdup(op)))
		return (NULL);
	ft_lstclear(&tokens, free);
	return (command);
}

static t_command
	*create_command(t_list *token_head)
{
	t_command	*new_command;

	if (!token_head || !(new_command = (t_command *)malloc(sizeof(t_command))))
		return (NULL);
	ft_memset(new_command, 0, sizeof(t_command));
	return (set_args_and_op(new_command, token_head));
}

static t_bool
	is_valid_command(t_command *c)
{
	t_command	*prev;

	prev = NULL;
	while (c)
	{
		if ((!(ft_strcmp(c->op, "|")) && !(c->args)) ||
			(!(ft_strcmp(c->op, ";")) && !(c->args)))
		{
			ft_put_syntaxerror_with_token(c->op);
			return (FALSE);
		}
		prev = c;
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
		while (!(ft_is_operator(((char*)tokens->content)[0])) && tokens->next)
			tokens = tokens->next;
		tmp = tokens->next;
		tokens->next = NULL;
		if (!(new_command = create_command(head)))
			return (clear_commands_and_tokens(commands, &head, &tmp));
		add_command(commands, new_command);
		if (!(is_valid_command(*commands)))
			return (clear_with_syntax_error(commands, NULL, &tmp));
		tokens = tmp;
	}
	return (COMPLETED);
}

#ifdef COMMANDTEST
static void
	print_args(t_list *args)
{
	if (!args)
		return ;
	ft_putstr_fd("-----args-----\n", STDOUT_FILENO);
	while (args)
	{
		ft_putstr_fd("[", STDOUT_FILENO);
		ft_putstr_fd(args->content, STDOUT_FILENO);
		ft_putstr_fd("]\n", STDOUT_FILENO);
		args = args->next;
	}
	ft_putstr_fd("--------------\n", STDOUT_FILENO);
}

int
	main(int ac, char **av)
{
	char		*line;
	char		*trimmed;
	extern char	**environ;
	t_list		*tokens;
	t_command	*head;
	t_command	*commands;

	if (ft_init_env() == STOP)
		return (EXIT_FAILURE);
	if (ft_init_pwd() == STOP)
	{
		ft_lstclear(&g_env, free);
		return (EXIT_FAILURE);
	}
	if (ac == 1)
	{
		ft_putstr_fd(PROMPT, STDOUT_FILENO);
		while (get_next_line(STDIN_FILENO, &line) == 1 &&
			(trimmed = ft_strtrim(line, " ")) &&
			(ft_strncmp(trimmed, "exit", 5)) &&
			(ft_make_token(&tokens, trimmed, ft_is_delimiter_or_quote) == COMPLETED) &&
			(ft_make_command(&commands, tokens) == COMPLETED))
		{
			head = commands;
			while (commands)
			{
				print_args(commands->args);
				ft_putstr_fd("op: ", STDOUT_FILENO);
				ft_putstr_fd("[", STDOUT_FILENO);
				ft_putstr_fd(commands->op, STDOUT_FILENO);
				ft_putstr_fd("]\n", STDOUT_FILENO);
				commands = commands->next;
			}
			FREE(line);
			FREE(trimmed);
			get_next_line(STDIN_FILENO, NULL);
			ft_clear_commands(&head);
			ft_putstr_fd(PROMPT, STDOUT_FILENO);
		}
		FREE(line);
		FREE(trimmed);
		get_next_line(STDIN_FILENO, NULL);
		ft_putstr_fd(EXIT_PROMPT, STDOUT_FILENO);
	}
	else
	{
		if ((trimmed = ft_strtrim(av[1], " ")) &&
			(ft_make_token(&tokens, trimmed, ft_is_delimiter_or_quote) == COMPLETED) &&
			(ft_make_command(&commands, tokens) == COMPLETED))
		{
			head = commands;
			while (commands)
			{
				print_args(commands->args);
				ft_putstr_fd("op: ", STDOUT_FILENO);
				ft_putstr_fd("[", STDOUT_FILENO);
				ft_putstr_fd(commands->op, STDOUT_FILENO);
				ft_putstr_fd("]\n", STDOUT_FILENO);
				commands = commands->next;
			}
			FREE(trimmed);
			ft_clear_commands(&head);
		}
	}
	FREE(g_pwd);
	ft_lstclear(&g_env, free);
	exit(g_status);
}
#endif
