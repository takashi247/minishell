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

static t_command
	*clear_commands_and_tokens(t_command **c, t_list **t1, t_list **t2)
{
	ft_lstclear(t1, free);
	ft_lstclear(t2, free);
	ft_clear_commands(c);
	return (NULL);
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

static t_bool
	convert_to_double_arrow(t_list **tokens)
{
	t_list	*tmp;

	FREE((*tokens)->content);
	if (!((*tokens)->content = ft_strdup(">>")))
		return (FALSE);
	tmp = (*tokens)->next->next;
	ft_lstdelone((*tokens)->next, free);
	(*tokens)->next = tmp;
	return (TRUE);
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
		if (((char*)tokens->content)[0] == '>' && tokens->next &&
			((char*)tokens->next->content)[0] == '>' &&
			!(convert_to_double_arrow(&tokens)))
			return (clear_commands_and_tokens(&command, &head, NULL));
		prev = tokens;
		tokens = tokens->next;
	}
	prev->next = NULL;
	command->args = head;
	op = !tokens ? ";" : (char*)tokens->content;
	if (!(command->op = ft_strdup(op)))
		return (clear_commands_and_tokens(&command, &head, &tokens));
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

t_command
	*ft_make_command(t_list *tokens)
{
	t_list		*head;
	t_list		*tmp;
	t_command	*head_command;
	t_command	*new_command;

	head_command = NULL;
	while (tokens)
	{
		head = tokens;
		while (!(ft_is_operator(((char*)tokens->content)[0])) && tokens->next)
			tokens = tokens->next;
		tmp = tokens->next;
		tokens->next = NULL;
		if (!(new_command = create_command(head)))
			return (clear_commands_and_tokens(&head_command, &head, &tmp));
		add_command(&head_command, new_command);
		tokens = tmp;
	}
	return (head_command);
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
	extern char	**environ;
	t_list		*tokens;
	t_command	*head;
	t_command	*commands;

	if (ac == 1)
	{
		ft_putstr_fd(PROMPT, STDOUT_FILENO);
		while (get_next_line(STDIN_FILENO, &line) == 1 &&
			(ft_strncmp(line, "exit", 5)))
		{
			if (!(tokens = ft_make_token(line)) || !(commands = ft_make_command(tokens)))
			{
				FREE(line);
				ft_lstclear(&tokens, free);
				return (1);
			}
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
			get_next_line(STDIN_FILENO, NULL);
			ft_clear_commands(&head);
			ft_putstr_fd(PROMPT, STDOUT_FILENO);
		}
		FREE(line);
		get_next_line(STDIN_FILENO, NULL);
		ft_putstr_fd(EXIT_PROMPT, STDOUT_FILENO);
	}
	else
	{
		if ((tokens = ft_make_token(av[1])) && (commands = ft_make_command(tokens)))
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
			ft_clear_commands(&head);
		}
	}
	exit(0);
}

#endif
