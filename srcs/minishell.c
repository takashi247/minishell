#include "minishell_tnishina.h"
#include "minishell_sikeda.h"
#include "libft.h"

int
	exit_with_error(char *str)
{
	printf("%s: %s\n", str, strerror(errno));
	exit(1);
}

void
	do_command(char *line, char **environ)
{
	char	**argv;

	argv = ft_split(line, ' ');
	argv[0] = ft_strjoin("/bin/", argv[0]);
	execve(argv[0], argv, environ);
	exit_with_error("execve");
}

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

static t_bool
	is_delimiter(char c)
{
	if (c == ' ' || c == '|' || c == '&' || c == ';' || c == '<' || c == '>')
		return (TRUE);
	else
		return (FALSE);
}

static t_bool
	is_valid_delimiter(char **line)
{
	
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
		while (!(is_delimiter(*line)) && *line)
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

char
	**ft_parse_line(char *line)
{
	char	**elems;
	int		num_elem;

	if (!line)
		return (NULL);
	num_elem = count_elems(line);
	if (!(elems = (char **)malloc(sizeof(char *) * (num_elem + 1))))
		return (NULL);
	return (split_elems(elems, line));
}

int
	main(void)
{
	char		*line;
	pid_t		pid;
	int			status;
	extern char	**environ;
	t_command	*command_head;
	char		**elems;

	command_head = NULL;
	ft_putstr_fd(PROMPT, STDOUT_FILENO);
	while (get_next_line(STDIN_FILENO, &line) == 1 &&
		(elems = ft_parse_line(line)) &&
		ft_load_command(elems, &command_head))
	{
		execute_commands(command_head);
		if ((pid = fork()) < 0)
			exit_with_error("fork");
		else if (pid == 0)
			do_command(line, environ);
		if ((pid = waitpid(pid, &status, 0)) < 0)
			exit_with_error("wait");
		FREE(line);
		FREE(elems);
		ft_clear_command(&command_head);
		ft_putstr_fd(PROMPT, STDOUT_FILENO);
	}
	FREE(line);
	FREE(elems);
	ft_putstr_fd(EXIT_PROMPT, STDOUT_FILENO);
	exit(0);
}
