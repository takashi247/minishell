#include "minishell_tnishina.h"

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
		g_ms.status = STATUS_GENERAL_ERR;
		ft_put_error(strerror(errno));
		ft_exit_n_free_g_vars(g_ms.status);
	}
	res = ft_validate_name(name);
	ft_free(&name);
	return (res);
}

/*
** fl[0]: a flag for single quotations ('\'')
** fl[1]: a flag for double quotations ('\"')
** fl[2]: a flag for equal signs ('=')
** fl[3]: a flag for backslashes ('\\')
*/

int
	ft_replace_env(t_list **args, int fl[4], int *i, t_bool is_rd)
{
	t_bool	has_name;
	int		env_pos[2];
	int		j;

	has_name = has_valid_name((char *)(*args)->content);
	env_pos[0] = *i;
	j = *i + 1;
	while (!(ft_is_env_name_end(((char *)(*args)->content)[j]))
		&& ((char*)(*args)->content)[j] != '?')
		j++;
	if (j - env_pos[0] == 1 && ((char *)(*args)->content)[j] == '?')
		j++;
	env_pos[1] = j;
	if (fl[1] || (has_name && fl[2]) || is_rd)
		return (ft_replace_q_env(((char **)&((*args)->content)), env_pos, i));
	else
		return (ft_replace_env_token(args, env_pos, i));
}
