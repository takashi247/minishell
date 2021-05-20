#include "minishell_tnishina.h"

static void
	put_env_with_export_syntax(const char *str, const int fd)
{
	if (!str)
		return ;
	ft_putstr_fd("declare -x ", fd);
	while (*str && *str != '=')
		ft_putchar_fd(*str++, fd);
	if (*str++ == '=')
	{
		ft_putstr_fd("=\"", fd);
		while (*str)
		{
			if (*str == '"' || *str == '$' || *str == '\\' || *str == '`')
				ft_putchar_fd('\\', fd);
			ft_putchar_fd(*str++, fd);
		}
		ft_putstr_fd("\"\n", fd);
	}
	else
		ft_putchar_fd('\n', fd);
}

int
	ft_print_export(void)
{
	t_list	*copy_env;
	t_list	*copy_env_head;

	copy_env = ft_copy_env();
	if (!copy_env)
		return (UTIL_ERROR);
	ft_envsort(&copy_env);
	copy_env_head = copy_env;
	while (copy_env)
	{
		put_env_with_export_syntax(copy_env->content, STDOUT_FILENO);
		copy_env = copy_env->next;
	}
	ft_clear_copied_env(&copy_env_head);
	return (UTIL_SUCCESS);
}
