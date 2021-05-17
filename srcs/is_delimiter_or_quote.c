#include "minishell_tnishina.h"
#include "minishell_sikeda.h"
#include "libft.h"

t_bool
	ft_is_delimiter(char c)
{
	if (c == ' ' || c == '|' || c == ';' || c == '<'
		|| c == '>' || !c || c == '\t')
		return (TRUE);
	else
		return (FALSE);
}

static void
	manage_flags(char *l, int i, int *fl)
{
	if (!fl[4] && l[i] == '\'' && !fl[0] && !fl[1])
		fl[0] = 1;
	else if (!fl[4] && l[i] == '\"' && !fl[0] && !fl[1])
		fl[1] = 1;
	else if (!fl[4] && l[i] == '\'' && fl[0] && !fl[1]
		&& !ft_is_delimiter(l[i + 1]))
		fl[0] = 0;
	else if (!fl[4] && l[i] == '\"' && !fl[0] && fl[1]
		&& !ft_is_delimiter(l[i + 1]))
		fl[1] = 0;
	else if (l[i] == '>' && l[i + 1] == '>')
		fl[2] = 1;
	else if (!i && ft_isdigit(l[i]))
		fl[3] = 1;
	else if (fl[3] && !ft_isdigit(l[i]))
		fl[3] = 0;
	else if (!fl[4] && l[i] == '\\')
		fl[4] = 1;
	else if (fl[4])
		fl[4] = 0;
}

t_bool
	ft_is_delimiter_or_quote(char *l, int i, int *fl)
{
	if ((!fl[0] && !fl[1] && !fl[4]
			&& (l[i] == '\0'
				|| (l[i] == ' ' || l[i] == '|' || l[i] == ';' || l[i] == '\t')
				|| (!fl[3] && l[i] == '<') || (!fl[3] && i && l[i] == '>')
				|| (!fl[3] && l[i] == '>' && l[i + 1] != '>')
				|| (fl[2] && l[i] == '>')))
		|| (l[i] == '\'' && fl[0] && ft_is_delimiter(l[i + 1]))
		|| (!fl[4] && l[i] == '\"' && fl[1] && ft_is_delimiter(l[i + 1]))
		|| ((fl[0] || fl[1]) && !l[i]))
		return (TRUE);
	else
	{
		manage_flags(l, i, fl);
		return (FALSE);
	}
}
