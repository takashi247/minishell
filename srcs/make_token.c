#include "minishell_tnishina.h"
#include "minishell_sikeda.h"
#include "libft.h"

static int
	exit_with_error(t_list **tokens, char **cpy)
{
	FREE(*cpy);
	ft_lstclear(tokens, free);
	return (FAILED);
}
/*
static void
	free_all_chars(char *tmp[2], char *new[3])
{
	FREE(tmp[0]);
	FREE(tmp[1]);
	FREE(new[0]);
	FREE(new[1]);
	FREE(new[2]);
}

static int
	replace_name_with_value(char **content, int env_pos[2])
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
	res = !ft_getenv(new[1]) ? ENV_DELETED : COMPLETED;
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

static int
	find_n_replace_env(char **content)
{
	int		i;
	int		j;
	int		env_pos[2];
	int		res;
	int		flag;

	i = 0;
	res = COMPLETED;
	while ((*content)[i])
	{
		flag = 1;
		if ((i == 0 || (*content)[i - 1] != '\\') && (*content)[i] == '$')
		{
			flag = 0;
			env_pos[0] = i;
			j = i + 1;
			while (!(is_env_name_end((*content)[j])))
				j++;
			env_pos[1] = j;
			if ((res = replace_name_with_value(content, env_pos)) == FAILED)
				return (res);
		}
		i += flag;
	}
	return (res);
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
	expand_env_var(t_list **tokens)
{
	t_list	*head;
	t_list	*prev;
	int		res;

	if (!*tokens)
		return (COMPLETED);
	head = *tokens;
	prev = NULL;
	while (*tokens)
	{
		if ((res = find_n_replace_env((char**)&((*tokens)->content))) ==
			COMPLETED)
		{
			prev = *tokens;
			*tokens = (*tokens)->next;
		}
		else if (res == FAILED)
			return (FAILED);
		else
			delete_token(tokens, &head, prev);
	}
	*tokens = head;
	return (COMPLETED);
}
*/

static t_bool
	is_delimiter_or_quote(char *l, int i, int *q)
{
	if ((!q[0] && !q[1] && (l[i] == ' ' || l[i] == '|' ||
		l[i] == '&' || l[i] == ';' || l[i] == '<' || l[i] == '>' ||
		l[i] == '\0')) || ((!i || l[i - 1] != '\\') && l[i] == '\'' &&
		q[0]) || ((!i || l[i - 1] != '\\') && l[i] == '\"' && q[1]) ||
		((q[0] || q[1]) && !l[i]))
		return (TRUE);
	else
	{
		if ((!i || l[i - 1] != '\\') && l[i] == '\'' && !q[0] && !q[1])
			q[0] = 1;
		else if ((!i || l[i - 1] != '\\') && l[i] == '\"' && !q[0] && !q[1])
			q[1] = 1;
		return (FALSE);
	}
}

static int
	put_quotation_error(char *cpy, t_list **tokens)
{
	ft_put_cmderror(cpy, QUOTATION_ERROR);
	ft_lstclear(tokens, free);
	g_status = 1;
	return (COMPLETED);
}

int
	ft_make_token(t_list **tokens, char *line)
{
	t_list	*new;
	int		i;
	char	*cpy;
	int		q[2];

	if (!line)
		return (COMPLETED);
	*tokens = NULL;
	while (*line)
	{
		i = 0;
		ft_memset(q, 0, sizeof(int) * 2);
		while (*line == ' ')
			line++;
		while (!(is_delimiter_or_quote(line, i, q)))
			i++;
		if (!(cpy = i != 0 && q[0] == 0 && q[1] == 0 ? ft_substr(line, 0, i) :
			ft_substr(line, 0, i + 1)) || !(new = ft_lstnew(cpy)))
			return (exit_with_error(tokens, &cpy));
		ft_lstadd_back(tokens, new);
		if ((q[0] || q[1]) && !line[i])
			return (put_quotation_error(cpy, tokens));
		line = line[i] ? line + i + (!i || q[0] || q[1]) : line + i;
	}
	return (COMPLETED);
}

#ifdef TOKENTEST
int
	main(int ac, char **av)
{
	char		*line;
	extern char	**environ;
	t_list		*tokens;
	t_list		*head;

	if (ft_init_env() == STOP)
		return (EXIT_FAILURE);
	if (ac == 1)
	{
		ft_putstr_fd(PROMPT, STDOUT_FILENO);
		while (get_next_line(STDIN_FILENO, &line) == 1 &&
			(ft_strncmp(line, "exit", 5)) &&
			(ft_make_token(&tokens, line) == COMPLETED))
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
		if ((ft_make_token(&tokens, av[1])) == COMPLETED)
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
	FREE(g_pwd);
	ft_lstclear(&g_env, free);
	exit(g_status);
}
#endif
