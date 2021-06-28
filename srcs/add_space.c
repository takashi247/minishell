#include "minishell_tnishina.h"

t_bool
	add_space_after_redirect(char **l, int *i)
{
	char	*tmp[2];
	char	*front;
	char	*back;
	t_bool	res;

	res = TRUE;
	tmp[0] = *l;
	front = ft_substr(*l, 0, *i + 1);
	back = ft_strdup(*l + *i + 1);
	tmp[1] = ft_strjoin(front, " ");
	*l = ft_strjoin(tmp[1], back);
	if (!front || !back || !tmp[1] || !(*l))
		res = FALSE;
	ft_free(&tmp[0]);
	ft_free(&tmp[1]);
	ft_free(&front);
	ft_free(&back);
	return (res);
}

/*
** f[2] is a flag array. Each of elements is a flag for the purpose explained
** below.
**
** f[0]: a flag for single quotations (')
** f[1]: a flag for double quotations (")
*/

void
	ft_add_space(char **l)
{
	int		i;
	int		fl[2];

	i = 0;
	ft_bzero(fl, sizeof(fl));
	while ((*l)[i])
	{
		if ((*l)[i] == '\'')
			fl[0] = !fl[0];
		else if ((*l)[i] == '\"')
			fl[1] = !fl[1];
		if (!fl[0] && !fl[1]
			&& (((*l)[i] == '<' && (*l)[i + 1] != '<')
				|| ((*l)[i] == '>' && (*l)[i + 1] != '>')))
		{
			if (!add_space_after_redirect(l, &i))
				ft_exit_n_free_g_vars(STATUS_GENERAL_ERR);
		}
		i++;
	}
}
