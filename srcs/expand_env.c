#include "minishell_tnishina.h"
#include "minishell_sikeda.h"
#include "libft.h"

static void
	free_all_chars(char *tmp[2], char *new[3])
{
	if (tmp)
	{
		ft_free(&tmp[0]);
		ft_free(&tmp[1]);
		ft_free(&tmp[2]);
	}
	if (new)
	{
		ft_free(&new[0]);
		ft_free(&new[1]);
		ft_free(&new[2]);
	}
}

static t_bool
	delete_env(t_list **tokens, t_list **head, t_list *prev, int res)
{
	char	*str;

	if (!prev)
	{
		if (res == TOKEN_DELETED || (*tokens)->next)
		{
			*head = (*tokens)->next;
			ft_lstdelone(*tokens, free);
			*tokens = *head;
		}
		else
		{
			str = ft_strdup("");
			if (!str)
			{
				g_status = 1;
				ft_lstdelone(*tokens, free);
				return (FALSE);
			}
			*head = ft_lstnew(str);
			ft_lstdelone(*tokens, free);
			*tokens = (*head)->next;
		}
	}
	else
	{
		prev->next = (*tokens)->next;
		ft_lstdelone(*tokens, free);
		*tokens = prev->next;
	}
	return (TRUE);
}

static int
	replace_env_in_quote(char **content, int *env_pos, int *i)
{
	char	*tmp[3];
	char	*new[3];
	int		p[2];
	int		res;

	ft_memset(tmp, 0, sizeof(tmp));
	ft_memset(new, 0, sizeof(new));
	tmp[0] = *content;
	p[0] = (*content)[env_pos[0] + 1] != '{' ? env_pos[0] + 1 : env_pos[0] + 2;
	p[1] = (*content)[env_pos[0] + 1] == '{' && (*content)[env_pos[1]] == '}' ?
		env_pos[1] + 1 : env_pos[1];
	new[0] = ft_substr(*content, 0, env_pos[0]);
	new[1] = ft_substr(*content, p[0], env_pos[1] - p[0]);
	new[2] = ft_strdup(*content + p[1]);
	if (!ft_strcmp(new[1], "\?"))
		tmp[1] = ft_itoa(g_status);
	else if (ft_getenv(new[1]))
		tmp[1] = ft_strdup(ft_getenv(new[1]));
	else
		tmp[1] = ft_strdup("");
	tmp[2] = ft_strjoin(new[0], tmp[1]);
	*content = ft_strjoin(tmp[2], new[2]);
	if (!new[0] || !new[1] || !new[2] || !tmp[1] || !tmp[2] || !(*content))
	{
		free_all_chars(tmp, new);
		return (FAILED);
	}
	*i += ft_strlen(tmp[1]);
	res = !(*content) ? ENV_DELETED : COMPLETED;
	free_all_chars(tmp, new);
	return (res);
}

static t_bool
	is_env_name_end(char c)
{
	if ((33 <= c && c <= 39) || (42 <= c && c <= 47) || c == 58 || c == 61 ||
		c == 64 || (91 <= c && c <= 94) || c == 96 || c == 123 ||
		(125 <= c && c <= 126) || c == ' ' || !c)
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
	replace_env_token(t_list **args, int *env_pos, int *i)
{
	t_list	*tokens;
	char	*tmp[2];
	char	*new[3];
	int		p[2];
	int		res;
	char	*env;

	tokens = NULL;
	ft_memset(tmp, 0, sizeof(tmp));
	ft_memset(new, 0, sizeof(new));
	p[0] = ((char*)(*args)->content)[env_pos[0] + 1] != '{' ? env_pos[0] + 1 : env_pos[0] + 2;
	p[1] = ((char*)(*args)->content)[env_pos[0] + 1] == '{' && ((char*)(*args)->content)[env_pos[1]] == '}' ?
		env_pos[1] + 1 : env_pos[1];
	new[0] = ft_substr((char*)(*args)->content, 0, env_pos[0]);
	new[1] = ft_substr((char*)(*args)->content, p[0], env_pos[1] - p[0]);
	new[2] = ft_strdup((char*)(*args)->content + p[1]);
	if (!ft_strcmp(new[1], "\?"))
		env = ft_itoa(g_status);
	else
	{
		if ((ft_getenv(new[1])))
			env = ft_strdup(ft_getenv(new[1]));
		else
			env = ft_strdup("");
	}
	if (!new[0] || !new[1] || !new[2] || !env ||
		ft_make_token(&tokens, env, is_space) == FAILED)
	{
		ft_free(&new[0]);
		ft_free(&new[1]);
		ft_free(&new[2]);
		ft_free(&env);
		return (FAILED);
	}
	ft_free(&env);
	if (tokens)
	{
		if (ft_lstsize(tokens) >= 2)
		{
			tmp[0] = ft_strjoin(new[0], (char *)tokens->content);
			tmp[1] = ft_strjoin((char *)ft_lstlast(tokens)->content, new[2]);
			if (!tmp[0] ||	!tmp[1])
			{
				ft_free(&new[0]);
				ft_free(&new[1]);
				ft_free(&new[2]);
				ft_free(&tmp[0]);
				ft_lstclear(&tokens, free);
				return (FAILED);
			}
			ft_free((char**)&((*args)->content));
			(*args)->content = tmp[0];
			ft_free((char**)&(ft_lstlast(tokens)->content));
			ft_lstlast(tokens)->content = tmp[1];
			ft_lstlast(tokens)->next = (*args)->next;
			(*args)->next = tokens->next;
			(*args) = ft_lstlast(tokens);
			*i = ft_strlen((char *)(*args)->content);
			ft_lstdelone(tokens, free);
		}
		else
		{
			*i += ft_strlen((char *)tokens->content);
			tmp[0] = ft_strjoin(new[0], (char *)tokens->content);
			tmp[1] = ft_strjoin(tmp[0], new[2]);
			if (!tmp[0] || !tmp[1])
			{
				ft_free(&new[0]);
				ft_free(&new[1]);
				ft_free(&new[2]);
				ft_free(&tmp[0]);
				ft_lstclear(&tokens, free);
				return (FAILED);
			}
			ft_free(&tmp[0]);
			ft_free((char **)&((*args)->content));
			(*args)->content = tmp[1];
			ft_lstdelone(tokens, free);
		}
		res = COMPLETED;
	}
	else
	{
		ft_free((char **)&((*args)->content));
		if (!((*args)->content = ft_strjoin(new[0], new[2])))
		{
			ft_free(&new[0]);
			ft_free(&new[1]);
			ft_free(&new[2]);
			return (FAILED);
		}
		if (ft_strlen((char *)(*args)->content))
			res = COMPLETED;
		else
			res = TOKEN_DELETED;
	}
	free_all_chars(NULL, new);
	return (res);
}

t_bool
	ft_remove_char(char **s, int i)
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
		g_status = 1;
		ft_free(&front);
		ft_free(&back);
		return (FALSE);
	}
	ft_free(&tmp);
	ft_free(&front);
	ft_free(&back);
	return (TRUE);
}

static t_bool
	check_quotation(char** s, int *i, int *q)
{
	if ((*s)[*i] == '\'' && !q[1])
	{
		q[0] = !q[0];
		return (ft_remove_char(s, *i));
	}
	else if ((*s)[*i] == '\"' && !q[0])
	{
		q[1] = !q[1];
		return (ft_remove_char(s, *i));
	}
	else if (((*s)[*i] == '\'' && q[1]) || ((*s)[*i] == '\"' && q[0]))
		(*i)++;
	return (TRUE);
}

t_bool
	ft_is_quote(char *s, int i)
{
	if (s[i] == '\'' || s[i] == '\"')
		return (TRUE);
	else
		return (FALSE);
}

t_bool
	ft_is_escapable_in_dquote(char c)
{
	if (c == '$' || c == '\"' || c == '\\')
		return (TRUE);
	else
		return (FALSE);
}

static t_bool
	has_valid_name(const char *content)
{
	char	*name;
	t_bool	res;

	if (!ft_strchr(content, '='))
		return (FALSE);
	name = ft_extract_envname_from_str(content);
	if (!name)
	{
		g_status = STATUS_GENERAL_ERR;
		ft_put_error(strerror(errno));
		ft_exit_n_free_g_vars(g_status);
	}
	res = ft_validate_name(name);
	ft_free(&name);
	return (res);
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
	int		b_flag;
	t_bool	has_name;
	int		equal_flag;

	i = 0;
	ft_memset(q_flag, 0, sizeof(q_flag));
	b_flag = 0;
	equal_flag = 0;
	has_name = has_valid_name((char *)(*args)->content);
	while ((*args)->content && ((char*)(*args)->content)[i])
	{
		flag = 1;
		if (((char *)(*args)->content)[i] == '=')
			equal_flag = 1;
		if (!b_flag && ((char *)(*args)->content)[i] == '\\' && !q_flag[0] && (!q_flag[1]
			|| ft_is_escapable_in_dquote(((char *)(*args)->content)[i + 1])))
		{
			b_flag = 1;
			if (!ft_remove_char((char **)&((*args)->content), i))
				return (FAILED);
			continue ;
		}
		if (!b_flag && ft_is_quote((char *)(*args)->content, i))
		{
			if (!check_quotation((char**)&((*args)->content), &i, q_flag))
				return (FAILED);
			continue ;
		}
		if (!(((char*)(*args)->content)[i]))
			break;
		if (!q_flag[0] && !b_flag && ((char*)(*args)->content)[i] == '$'
			&& !(is_env_name_end(((char *)(*args)->content)[i + 1])))
		{
			flag = 0;
			env_pos[0] = i;
			j = i + 1;
			while (!(is_env_name_end(((char*)(*args)->content)[j]))
				&& ((char*)(*args)->content)[j] != '?')
				j++;
			if (j - env_pos[0] == 1 && ((char*)(*args)->content)[j] == '?')
				j++;
			env_pos[1] = j;
			if (q_flag[1] || (has_name && equal_flag))
			{
				res = replace_env_in_quote(((char**)&((*args)->content)), env_pos, &i);
				if (res == FAILED)
					return (FAILED);
				else if (res == ENV_DELETED)
					return (ENV_DELETED);
			}
			else
			{
				res = replace_env_token(args, env_pos, &i);
				if (res == FAILED)
					return (FAILED);
				else if (res == TOKEN_DELETED)
					return (TOKEN_DELETED);
			}
		}
		i += flag;
		b_flag = 0;
	}
	return (COMPLETED);
}

static int
	expand_list(t_list **head)
{
	t_list	*current;
	t_list	*prev;
	char	*pre_expand;
	int		res;

	if (!(*head))
		return (COMPLETED);
	current = *head;
	prev = NULL;
	while (current)
	{
		pre_expand = ft_strdup((char *)current->content);
		res = find_n_replace_env(&current);
		if (res == COMPLETED)
		{
			prev = current;
			current = current->next;
		}
		else if (res == FAILED)
		{
			ft_free(&pre_expand);
			break;
		}
		else
		{
			if (prev && ft_is_redirect((char *)prev->content))
			{
				ft_put_cmderror(pre_expand, AMBIGUOUS_REDIRECT_ERR_MSG);
				g_status = STATUS_GENERAL_ERR;
				ft_free(&pre_expand);
				return (REDIRECT_DELETED);
			}
			else if (!delete_env(&current, head, prev, res))
			{
				ft_free(&pre_expand);
				return (FAILED);
			}
		}
		ft_free(&pre_expand);
	}
	return (res);
}

int
	ft_expand_env_var(t_command *c)
{
	int	exp_args_res;
	int	exp_redirect_res;

	if (!c || c->expanded)
		return (COMPLETED);
	else
	{
		exp_args_res = expand_list(&(c->args));
		exp_redirect_res = expand_list(&(c->redirects));
		if (exp_args_res == FAILED
		|| exp_redirect_res == FAILED)
			return (FAILED);
		else if (exp_redirect_res == REDIRECT_DELETED)
			return (REDIRECT_DELETED);
		c->expanded = TRUE;
		return (COMPLETED);
	}
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
