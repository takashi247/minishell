#include "minishell_sikeda.h"
#include "minishell_tnishina.h"
#include "libft.h"

static int
	del_escape(char **s)
{
	int		i;

	i = 0;

	while ((*s)[i])
	{
		if ((*s)[i] == '\\' && (*s)[i + 1] != '\\')
		{
			if (!(ft_remove_char(s, i)))
				return (FALSE);
		}
		else
			i++;
	}
	return (TRUE);
}

int
	ft_remove_escape(t_list *lst)
{
	while (lst)
	{
		if (del_escape((char **)&(lst->content)) == FAILED)
			return (FAILED);
		lst = lst->next;
	}
	return (COMPLETED);
}