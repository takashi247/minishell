#include "minishell.h"

static int
	exit_w_quotation_error(char *cpy, t_list **tokens)
{
	ft_put_cmderror(cpy, MULTILINE_ERROR_MSG);
	ft_lstclear(tokens, free);
	g_ms.status = STATUS_GENERAL_ERR;
	return (COMPLETED);
}

/*
** f[5] is a flag array. Each of elements is a flag for the purpose explained
** below.
**
** f[0]: a flag for single quotations (')
** f[1]: a flag for double quotations (")
** f[2]: a flag for double right arrows (>>)
** f[3]: a flag for file descriptor before arrow (1>, 2>, etc.)
** f[4]: a flag for escape character (\)
** f[5]: a flag for double left arrows (<<)
*/

static void
	update_c_pointer(char **l, int i, int fl[6])
{
	if ((*l)[i])
		*l = *l + i + (!i || fl[0] || fl[1] || fl[2] || fl[5]);
	else
		*l = *l + i;
}

static t_list
	*tokenize_word(char *l, int i, int fl[6])
{
	char	*cpy;

	if (i != 0 && !fl[0] && !fl[1] && !fl[2] && !fl[5])
		cpy = ft_substr(l, 0, i);
	else
		cpy = ft_substr(l, 0, i + 1);
	if (!cpy)
		return (NULL);
	return (ft_lstnew(cpy));
}

int
	ft_make_token(t_list **tokens, char *l, t_bool(*f)(char*, int, int*))
{
	t_list	*n;
	int		i;
	int		fl[6];

	*tokens = NULL;
	if (!l)
		return (COMPLETED);
	while (*l)
	{
		i = 0;
		ft_bzero(fl, sizeof(fl));
		while (*l == ' ' || *l == '\t')
			l++;
		while (!(f(l, i, fl)))
			i++;
		n = tokenize_word(l, i, fl);
		if (!n)
			return (FAILED);
		ft_lstadd_back(tokens, n);
		if ((fl[0] || fl[1]) && !l[i])
			return (exit_w_quotation_error((char *)n->content, tokens));
		update_c_pointer(&l, i, fl);
	}
	return (COMPLETED);
}
