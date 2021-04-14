#include "minishell_tnishina.h"
#include "minishell_sikeda.h"
#include "libft.h"

static void
	free_all_chars(char *tmp[2], char *new[3])
{
	if (tmp)
	{
		FREE(tmp[0]);
		FREE(tmp[1]);
	}
	if (new)
	{
		FREE(new[0]);
		FREE(new[1]);
		FREE(new[2]);
	}
}

static void
	delete_token(t_list **tokens, t_list **head, t_list *prev)
{
	if (!prev)
	{
		*head = (*tokens)->next;
		ft_lstdelone(*tokens, free);
		*tokens = *head;
	}
	else
	{
		prev->next = (*tokens)->next;
		ft_lstdelone(*tokens, free);
		*tokens = prev->next;
	}
}

static int
	replace_name_with_value(char **content, int *env_pos)
{
	char	*tmp[2];
	char	*new[3];
	int		p[2];
	int		res;

	ft_memset(tmp, 0, sizeof(char*) * 2);
	ft_memset(new, 0, sizeof(char*) * 3);
	tmp[0] = *content;
	p[0] = (*content)[env_pos[0] + 1] != '{' ? env_pos[0] + 1 : env_pos[0] + 2;
	p[1] = (*content)[env_pos[0] + 1] == '{' && (*content)[env_pos[1]] == '}' ?
		env_pos[1] + 1 : env_pos[1];
	if (!(new[0] = ft_substr(*content, 0, env_pos[0])) ||
		!(new[1] = ft_substr(*content, p[0], env_pos[1] - p[0])) ||
		!(new[2] = ft_strdup(*content + p[1])) ||
		!(tmp[1] = ft_strjoin(new[0], ft_getenv(new[1]))) ||
		!(*content = ft_strjoin(tmp[1], new[2])))
	{
		free_all_chars(tmp, new);
		FREE(*content);
		return (FAILED);
	}
	res = !(*content) ? ENV_DELETED : COMPLETED;
	free_all_chars(tmp, new);
	return (res);
}

static t_bool
	is_env_name_end(char c)
{
	if ((33 <= c && c <= 39) || (42 <= c && c <= 47) || c == 58 || c == 61 ||
		(63 <= c && c <= 64) || (91 <= c && c <= 96) || c == 123 ||
		(125 <= c && c <= 126) || !c || c == ' ')
		return (TRUE);
	else
		return (FALSE);
}

static t_bool
	is_space(char *l, int i, int *fl)
{
	if ((!fl[0] && !fl[1] && (l[i] == '\0' || l[i] == ' ')))
		return (TRUE);
	else
		return (FALSE);
}

static int
	replace_env_with_token(t_list **args, int *env_pos)
{
	t_list	*tokens;
	char	*tmp[2];
	char	*new[3];
	int		p[2];
	int		res;

	tokens = NULL;
	ft_memset(tmp, 0, sizeof(char*) * 2);
	ft_memset(new, 0, sizeof(char*) * 3);
	p[0] = ((char*)(*args)->content)[env_pos[0] + 1] != '{' ? env_pos[0] + 1 : env_pos[0] + 2;
	p[1] = ((char*)(*args)->content)[env_pos[0] + 1] == '{' && ((char*)(*args)->content)[env_pos[1]] == '}' ?
		env_pos[1] + 1 : env_pos[1];
	if (!(new[0] = ft_substr((char*)(*args)->content, 0, env_pos[0])) ||
		!(new[1] = ft_substr((char*)(*args)->content, p[0], env_pos[1] - p[0])) ||
		!(new[2] = ft_strdup((char*)(*args)->content + p[1])) ||
		ft_make_token(&tokens, ft_getenv(new[1]), is_space) == FAILED)
	{
		FREE(new[0]);
		FREE(new[1]);
		FREE(new[2]);
		return (FAILED);
	}
	if (tokens)
	{
		if (ft_lstsize(tokens) >= 2)
		{
			if (!(tmp[0] = ft_strjoin(new[0], (char*)tokens->content)) ||
			!(tmp[1] = ft_strjoin((char*)ft_lstlast(tokens)->content, new[2])))
			{
				FREE(new[0]);
				FREE(new[1]);
				FREE(new[2]);
				FREE(tmp[0]);
				return (FAILED);
			}
			FREE((*args)->content);
			(*args)->content = tmp[0];
			FREE(ft_lstlast(tokens)->content);
			ft_lstlast(tokens)->content = tmp[1];
			ft_lstlast(tokens)->next = (*args)->next;
			(*args)->next = tokens->next;
			ft_lstdelone(tokens, free);
		}
		else
		{
			if (!(tmp[0] = ft_strjoin(new[0], (char*)tokens->content)) ||
			!(tmp[1] = ft_strjoin(tmp[0], new[2])))
			{
				FREE(new[0]);
				FREE(new[1]);
				FREE(new[2]);
				FREE(tmp[0]);
				return (FAILED);
			}
			FREE(tmp[0]);
			FREE((*args)->content);
			(*args)->content = tmp[1];
			ft_lstdelone(tokens, free);
		}
	}
	else
	{
		FREE((*args)->content);
		if (!((*args)->content = ft_strjoin(new[0], new[2])))
		{
			FREE(new[0]);
			FREE(new[1]);
			FREE(new[2]);
			return (FAILED);
		}
	}
	res = !((*args)->content) ? ENV_DELETED : COMPLETED;
	free_all_chars(NULL, new);
	return (res);
}

static t_bool
	remove_quotation(char **s, int i)
{
	char	*tmp;
	char	*front;
	char	*back;

	tmp = *s;
	front = NULL;
	back = NULL;
	if (!(front = ft_substr(*s, 0, i)) || !(back = ft_strdup(*s + i + 1)) ||
	!(*s = ft_strjoin(front, back)))
	{
		FREE(front);
		FREE(back);
		return (FALSE);
	}
	FREE(tmp);
	FREE(front);
	FREE(back);
	return (TRUE);
}

static t_bool
	check_quotation(char** s, int i, int *q)
{
	if ((!i || (*s)[i - 1] != '\\') && (*s)[i] == '\'' && !q[1])
	{
		q[0] = !q[0];
		return (remove_quotation(s, i));
	}
	else if ((!i || (*s)[i - 1] != '\\') && (*s)[i] == '\"' && !q[0])
	{
		q[1] = !q[1];
		return (remove_quotation(s, i));
	}
	return (TRUE);
}

static int
	find_n_replace_env(t_list **args)
{
	int		i;
	int		j;
	int		env_pos[2];
	int		flag;
	int		q_flag[2];
	int		res;

	i = 0;
	res = COMPLETED;
	ft_memset(q_flag, 0, sizeof(int) * 2);
	while (((char*)(*args)->content)[i])
	{
		flag = 1;
		if (!check_quotation(((char**)&(*args)->content), i, q_flag))
			return (FAILED);
		if (!(((char*)(*args)->content)[i]))
			break;
		if (!q_flag[0] && (i == 0 || ((char*)(*args)->content)[i - 1] != '\\') && ((char*)(*args)->content)[i] == '$')
		{
			flag = 0;
			env_pos[0] = i;
			j = i + 1;
			while (!(is_env_name_end(((char*)(*args)->content)[j])))
				j++;
			env_pos[1] = j;
			if (q_flag[1] && ((res = replace_name_with_value(((char**)&(*args)->content), env_pos)) == FAILED))
				return (FAILED);
			else if (!q_flag[1] && (res = replace_env_with_token(args, env_pos)) == FAILED)
				return (FAILED);
		}
		i += flag;
	}
	res = !(ft_strlen(((char*)(*args)->content))) ? ENV_DELETED : res;
	return (res);
}

int
	ft_expand_env_var(t_command *c)
{
	t_list	*head;
	t_list	*prev;
	int		res;

	if (!c)
		return (COMPLETED);
	head = c->args;
	prev = NULL;
	while (c->args)
	{
		if ((res = find_n_replace_env(&(c->args))) == COMPLETED)
		{
			prev = c->args;
			c->args = c->args->next;
		}
		else if (res == FAILED)
			return (FAILED);
		else
			delete_token(&(c->args), &head, prev);
	}
	c->args = head;
	return (COMPLETED);
}

#ifdef EXPANDTEST
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
			commands = head;
			ft_putstr_fd("=====After expansion=====\n", STDOUT_FILENO);
			while (commands)
			{
				ft_expand_env_var(commands);
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
			commands = head;
			ft_putstr_fd("=====After expansion=====\n", STDOUT_FILENO);
			while (commands)
			{
				ft_expand_env_var(commands);
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
