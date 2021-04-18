#include "minishell_tnishina.h"
#include "minishell_sikeda.h"
#include "libft.h"

static int
	exit_with_error(t_list **tokens, char **cpy)
{
	FREE(*cpy);
	ft_lstclear(tokens, free);
	g_status = STATUS_GENERAL_ERR;
	return (FAILED);
}

t_bool
	ft_is_delimiter(char c)
{
	if (c == ' ' || c == '|' || c == ';' || c == '<' || c == '>' || !c)
		return (TRUE);
	else
		return (FALSE);
}

t_bool
	ft_is_delimiter_or_quote(char *l, int i, int *fl)
{
	if ((!fl[0] && !fl[1] && (l[i] == '\0' || l[i] == ' ' || l[i] == '|' || l[i] == ';' || l[i] == '<' ||
		(i && l[i] == '>') || (l[i] == '>' && l[i + 1] != '>'))) ||
		((!i || l[i - 1] != '\\') && l[i] == '\'' && fl[0] && ft_is_delimiter(l[i + 1])) ||
		((!i || l[i - 1] != '\\') && l[i] == '\"' && fl[1] && ft_is_delimiter(l[i + 1])) ||
		((fl[0] || fl[1]) && !l[i]))
		return (TRUE);
	else
	{
		if ((!i || l[i - 1] != '\\') && l[i] == '\'' && !fl[0] && !fl[1])
			fl[0] = 1;
		else if ((!i || l[i - 1] != '\\') && l[i] == '\"' && !fl[0] && !fl[1])
			fl[1] = 1;
		else if ((!i || l[i - 1] != '\\') && l[i] == '\'' && fl[0] && !ft_is_delimiter(l[i + 1]))
			fl[0] = 0;
		else if ((!i || l[i - 1] != '\\') && l[i] == '\"' && fl[1] && !ft_is_delimiter(l[i + 1]))
			fl[1] = 0;
		else if (l[i] == '>' && l[i + 1] == '>')
			fl[2] = 1;
		return (FALSE);
	}
}

static int
	put_quotation_error(char *cpy, t_list **tokens)
{
	ft_put_cmderror(cpy, QUOTATION_ERROR_MSG);
	ft_lstclear(tokens, free);
	g_status = 1;
	return (COMPLETED);
}

/*
** f[3] is a flag array. Each of elements is a flag for the purpose explained
** below.
**
** f[0]: a flag for single quotations (')
** f[1]: a flag for double quotations (")
** f[2]: a flag for double arrows (>>)
*/

int
	ft_make_token(t_list **tokens, char *l, t_bool(*f)(char*, int, int*))
{
	t_list	*n;
	int		i;
	char	*cpy;
	int		fl[3];

	*tokens = NULL;
	if (!l)
		return (COMPLETED);
	while (*l)
	{
		i = 0;
		ft_memset(fl, 0, sizeof(int) * 3);
		while (*l == ' ')
			l++;
		while (!(f(l, i, fl)))
			i++;
		if (!(cpy = i != 0 && fl[0] == 0 && fl[1] == 0 && fl[2] == 0 ?
		ft_substr(l, 0, i) : ft_substr(l, 0, i + 1)) || !(n = ft_lstnew(cpy)))
			return (exit_with_error(tokens, &cpy));
		ft_lstadd_back(tokens, n);
		if ((fl[0] || fl[1]) && !l[i])
			return (put_quotation_error(cpy, tokens));
		l = l[i] ? l + i + (!i || fl[0] || fl[1] || fl[2]) : l + i;
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
			(ft_make_token(&tokens, line, ft_is_delimiter_or_quote) == COMPLETED))
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
		if ((ft_make_token(&tokens, av[1], ft_is_delimiter_or_quote)) == COMPLETED)
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
