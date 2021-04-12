#include "../includes/minishell_sikeda.h"

static int
	init_env_list(const char *current, const int i)
{
	t_list	*new;
	char	*cpy;

	if (!(cpy = ft_strdup(current)) || !(new = ft_lstnew(cpy)))
	{
		cpy ? FREE(cpy) : cpy;
		ft_lstclear(&g_env, free);
		return (STOP);
	}
	if (i == 0)
		g_env = new;
	else
		ft_lstadd_back(&g_env, new);
	return (KEEP_RUNNING);
}

static int
	update_shlvl(const char *next_level, const int current_level)
{
	if (999 < current_level)
	{
		ft_putstr_fd(PRG_NAME, STDERR_FILENO);
		ft_putstr_fd(": warning: shell level (", STDERR_FILENO);
		ft_putstr_fd((char*)next_level, STDERR_FILENO);
		ft_putendl_fd(") too high, resetting to 1", STDERR_FILENO);
		return (ft_setenv_sep("SHLVL", "1"));
	}
	else if (current_level == 999)
		return (ft_setenv_sep("SHLVL", ""));
	else if (current_level < 0)
		return (ft_setenv_sep("SHLVL", "0"));
	else
		return (ft_setenv_sep("SHLVL", (char*)next_level));
}

static int
	init_shlvl(void)
{
	char	*shlvl;
	char	*next_level;
	int64_t	current_level;
	int		result;

	shlvl = ft_getenv("SHLVL");
	if (shlvl)
	{
		current_level = ft_atoi(shlvl);
		current_level = (INT_MAX - 1) < current_level ? -1 : current_level;
		if (!(next_level = ft_itoa(current_level + 1)))
		{
			ft_put_error(strerror(errno));
			return (STOP);
		}
		result = update_shlvl(next_level, current_level);
		FREE(next_level);
	}
	else
		result = ft_setenv_sep("SHLVL", "1");
	return (result == UTIL_ERROR ? STOP : KEEP_RUNNING);
}

int
	ft_init_env(void)
{
	extern char	**environ;
	int			i;

	i = 0;
	while (environ[i])
	{
		if (!ft_strncmp(environ[i], "OLDPWD=", ft_strlen("OLDPWD=")))
		{
			i++;
			continue ;
		}
		if (init_env_list(environ[i], i) == STOP)
			return (STOP);
		i++;
	}
	if (init_env_list("OLDPWD", i++) == STOP)
		return (STOP);
	return (init_shlvl());
}
