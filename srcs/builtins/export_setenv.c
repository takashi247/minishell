#include "minishell.h"

#ifdef EXPORTTEST
static void
	test_print_export(void)
{
	ft_print_export();
}

#else
static void
	test_print_export(void)
{
}
#endif

static int
	env_append(const char *name, char **value)
{
	char	*join;
	int		ret;

	ret = KEEP_RUNNING;
	join = ft_getenv(name);
	if (join)
	{
		join = ft_strjoin(join, *value);
		if (join)
		{
			ft_free(value);
			*value = join;
		}
		else
			ret = STOP;
	}
	if (join && ft_setenv_sep(name, *value) == UTIL_ERROR)
		ret = STOP;
	return (ret);
}

static int
	get_value(char **args, char **value)
{
	*value = NULL;
	if (ft_strchr(args[1], '='))
	{
		*value = ft_extract_envvalue_from_str(args[1]);
		if (!*value)
			return (UTIL_ERROR);
	}
	else if (!ft_strcmp("PWD", args[1]))
	{
		*value = ft_strdup(g_ms.pwd);
		if (!*value)
			return (UTIL_ERROR);
	}
	else if (!ft_strcmp("OLDPWD", args[1]))
	{
		if (g_ms.sh_oldpwd)
		{
			*value = ft_strdup(g_ms.sh_oldpwd);
			if (!*value)
				return (UTIL_ERROR);
		}
	}
	return (UTIL_SUCCESS);
}

int
	ft_export_setenv(char **args, const char *name, const t_bool plus_mode)
{
	char	*value;
	int		ret;

	if (get_value(args, &value) == UTIL_ERROR)
		return (STOP);
	ret = KEEP_RUNNING;
	if (plus_mode == FALSE && (!ft_getenv(name) || ft_strchr(args[1], '=')))
	{
		if (ft_setenv_sep(name, value) == UTIL_ERROR)
			ret = STOP;
		test_print_export();
	}
	else if (plus_mode == TRUE)
	{
		ret = env_append(name, &value);
		if (ret == KEEP_RUNNING)
			test_print_export();
	}
	ft_free(&value);
	return (ret);
}
