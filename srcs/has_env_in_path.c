#include "minishell_tnishina.h"

/*
** fl[0]: a flag for single quotations ('\'')
** fl[1]: a flag for double quotations ('\"')
** fl[2]: a flag for equal signs ('=')
** fl[3]: a flag for backslashes ('\\')
*/

static void
	check_quotation(char *s, int *i, int fl[4])
{
	if (s[*i] == '\'' && !fl[1])
	{
		fl[0] = !fl[0];
		(*i)++;
	}
	else if (s[*i] == '\"' && !fl[0])
	{
		fl[1] = !fl[1];
		(*i)++;
	}
	else if ((s[*i] == '\'' && fl[1]) || (s[*i] == '\"' && fl[0]))
		(*i)++;
}

/*
** fl[0]: a flag for single quotations ('\'')
** fl[1]: a flag for double quotations ('\"')
** fl[2]: a flag for equal signs ('=')
** fl[3]: a flag for backslashes ('\\')
*/

static int
	check_conditions(char *path, int *i, int fl[4])
{
	if (path[*i] == '=')
	{
		fl[2] = 1;
		(*i)++;
		return (CONDITIONS_MET);
	}
	else if (!fl[3] && path[*i] == '\\' && !fl[0] && (!fl[1]
			|| ft_is_escapable_in_dquote(path[(*i) + 1])))
	{
		fl[3] = 1;
		(*i)++;
		return (CONDITIONS_MET);
	}
	else if (!fl[3] && ft_is_quote(path, *i))
	{
		check_quotation(path, i, fl);
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

t_bool
	ft_has_env_in_path(char *path)
{
	int		i;
	int		fl[4];

	i = 0;
	ft_memset(fl, 0, sizeof(fl));
	while (path[i])
	{
		if (check_conditions(path, &i, fl) == CONDITIONS_MET)
			continue ;
		if (!fl[0] && !fl[3]
			&& (path[i] == '$'
				&& !(ft_is_env_name_end(path[i + 1]))))
			return (TRUE);
		else
			i++;
		fl[3] = 0;
	}
	return (FALSE);
}
