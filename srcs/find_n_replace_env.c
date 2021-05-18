#include "minishell_tnishina.h"
#include "minishell_sikeda.h"
#include "libft.h"

/*
** fl[0]: a flag for single quotations ('\'')
** fl[1]: a flag for double quotations ('\"')
** fl[2]: a flag for equal signs ('=')
** fl[3]: a flag for backslashes ('\\')
*/

static t_bool
	check_quotation(char **s, int *i, int fl[4])
{
	if ((*s)[*i] == '\'' && !fl[1])
	{
		fl[0] = !fl[0];
		return (ft_remove_char(s, *i));
	}
	else if ((*s)[*i] == '\"' && !fl[0])
	{
		fl[1] = !fl[1];
		return (ft_remove_char(s, *i));
	}
	else if (((*s)[*i] == '\'' && fl[1]) || ((*s)[*i] == '\"' && fl[0]))
		(*i)++;
	return (TRUE);
}

/*
** fl[0]: a flag for single quotations ('\'')
** fl[1]: a flag for double quotations ('\"')
** fl[2]: a flag for equal signs ('=')
** fl[3]: a flag for backslashes ('\\')
*/

static int
	check_conditions(char **arg, int *i, int fl[4])
{
	if ((*arg)[*i] == '=')
	{
		fl[2] = 1;
		(*i)++;
		return (CONDITIONS_MET);
	}
	else if (!fl[3] && (*arg)[*i] == '\\' && !fl[0] && (!fl[1]
			|| ft_is_escapable_in_dquote((*arg)[(*i) + 1])))
	{
		fl[3] = 1;
		if (!ft_remove_char(arg, *i))
			return (FAILED);
		return (CONDITIONS_MET);
	}
	else if (!fl[3] && ft_is_quote(*arg, *i))
	{
		if (!check_quotation(arg, i, fl))
			return (FAILED);
		return (CONDITIONS_MET);
	}
	return (COMPLETED);
}

/*
** fl[0]: a flag for single quotations ('\'')
** fl[1]: a flag for double quotations ('\"')
** fl[2]: a flag for equal signs ('=')
** fl[3]: a flag for backslashes ('\\')
*/

int
	ft_find_n_replace_env(t_list **args)
{
	int		i;
	int		fl[4];
	int		res;

	i = 0;
	ft_memset(fl, 0, sizeof(fl));
	while ((*args)->content && ((char *)(*args)->content)[i])
	{
		res = check_conditions((char **)&(*args)->content, &i, fl);
		if (res == CONDITIONS_MET)
			continue ;
		else if (res == FAILED)
			return (res);
		if (!fl[0] && !fl[3] && ((char *)(*args)->content)[i] == '$'
			&& !(ft_is_env_name_end(((char *)(*args)->content)[i + 1])))
		{
			res = ft_replace_env(args, fl[1], fl[2], &i);
			if (res == FAILED || res == ENV_DELETED || res == TOKEN_DELETED)
				return (res);
		}
		else
			i++;
		fl[3] = 0;
	}
	return (COMPLETED);
}
