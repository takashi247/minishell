#include "minishell.h"

/* return zero when overflow and check char after number */
static int
	shlvl_atoi(const char *str)
{
	uint64_t	num;
	int			sign;

	num = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str++ == '-')
			sign = -1;
	}
	while (ft_isdigit(*str))
	{
		num = (num * 10) + (*str++ - '0');
		if (num >> 63)
			return (0);
	}
	if (*str && !(*str == ' ' || *str == '\n' || *str == '\t'))
		return (0);
	return (sign * num);
}

static int
	init_env_list(const char *current, const int i)
{
	t_list	*new;
	char	*cpy;

	cpy = ft_strdup(current);
	new = NULL;
	if (cpy)
		new = ft_lstnew(cpy);
	if (!new)
	{
		if (cpy)
			ft_free(&cpy);
		ft_lstclear(&g_ms.env, free);
		return (STOP);
	}
	if (i == 0)
		g_ms.env = new;
	else
		ft_lstadd_back(&g_ms.env, new);
	return (KEEP_RUNNING);
}

static int
	update_shlvl(const char *next_level, const int current_level)
{
	if (999 < current_level)
	{
		ft_putstr_fd(PRG_NAME, STDERR_FILENO);
		ft_putstr_fd(": warning: shell level (", STDERR_FILENO);
		ft_putstr_fd((char *)next_level, STDERR_FILENO);
		ft_putendl_fd(") too high, resetting to 1", STDERR_FILENO);
		return (ft_setenv_sep("SHLVL", "1"));
	}
	else if (current_level == 999)
		return (ft_setenv_sep("SHLVL", ""));
	else if (current_level < 0)
		return (ft_setenv_sep("SHLVL", "0"));
	else
		return (ft_setenv_sep("SHLVL", (char *)next_level));
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
		current_level = shlvl_atoi(shlvl);
		if ((INT_MAX - 1) < current_level)
			current_level = -1;
		next_level = ft_itoa(current_level + 1);
		if (!next_level)
		{
			ft_put_error(strerror(errno));
			return (STOP);
		}
		result = update_shlvl(next_level, current_level);
		ft_free(&next_level);
	}
	else
		result = ft_setenv_sep("SHLVL", "1");
	if (result == UTIL_ERROR)
		return (STOP);
	return (KEEP_RUNNING);
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
