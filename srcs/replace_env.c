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

int
	ft_replace_env(t_list **args, int dq_flag, int eq_flag, int *i)
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
	if (dq_flag || (has_name && eq_flag))
		return (ft_replace_q_env(((char **)&((*args)->content)), env_pos, i));
	else
		return (ft_replace_env_token(args, env_pos, i));
}
