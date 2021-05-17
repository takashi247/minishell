#include "minishell_tnishina.h"
#include "minishell_sikeda.h"
#include "libft.h"

t_bool
	ft_is_space(char *l, int i, int *fl)
{
	if ((!fl[0] && !fl[1] && (l[i] == '\0' || l[i] == ' ')))
		return (TRUE);
	else
		return (FALSE);
}

t_bool
	ft_remove_char(char **s, int i)
{
	char	*tmp;
	char	*front;
	char	*back;

	tmp = *s;
	front = ft_substr(*s, 0, i);
	back = ft_strdup(*s + i + 1);
	if (front && back)
		*s = ft_strjoin(front, back);
	if (!front || !back || !(*s))
	{
		g_status = STATUS_GENERAL_ERR;
		ft_free(&front);
		ft_free(&back);
		return (FALSE);
	}
	ft_free(&tmp);
	ft_free(&front);
	ft_free(&back);
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

t_bool
	ft_is_env_name_end(char c)
{
	if ((33 <= c && c <= 39) || (42 <= c && c <= 47) || c == 58 || c == 61
		|| c == 64 || (91 <= c && c <= 94) || c == 96 || c == 123
		|| (125 <= c && c <= 126) || c == ' ' || !c)
		return (TRUE);
	else
		return (FALSE);
}
