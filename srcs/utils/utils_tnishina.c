#include "minishell_tnishina.h"

char
	**ft_convert_list(t_list *l)
{
	char	**argv;
	char	**head;

	if (!l)
		return (NULL);
	argv = (char **)malloc(sizeof(char *) * (ft_lstsize(l) + 1));
	if (!argv)
		return (NULL);
	head = argv;
	ft_memset(argv, 0, sizeof(char *) * (ft_lstsize(l) + 1));
	while (l)
	{
		*argv = ft_strdup((char *)(l->content));
		if (!*argv)
		{
			ft_clear_argv(&head);
			ft_put_error(strerror(errno));
			return (NULL);
		}
		argv++;
		l = l->next;
	}
	*argv = NULL;
	return (head);
}

void
	ft_clear_argv(char ***argv)
{
	char	**head;

	if (*argv)
		head = *argv;
	while (**argv)
	{
		ft_free(*argv);
		(*argv)++;
	}
	free(head);
	head = NULL;
}

int
	ft_isover_intrange(char *s)
{
	uint64_t	num;
	int			is_minus;

	is_minus = 0;
	while (ft_isspace(*s))
		s++;
	if (*s == '-')
		is_minus = 1;
	if (*s == '+' || *s == '-')
		s++;
	num = 0;
	while (ft_isdigit(*s))
	{
		num = num * 10 + *s - '0';
		if (is_minus && (int64_t)__INT_MAX__ + 1 < num)
			return (-1);
		else if (!is_minus && (uint64_t)__INT_MAX__ < num)
			return (1);
		s++;
	}
	return (0);
}

void
	ft_exit_n_free_g_vars(int exit_status)
{
	ft_free(&g_ms.pwd);
	ft_free(&g_ms.err_arg);
	ft_free(&g_ms.err_msg);
	ft_free(&g_ms.sh_pwd);
	ft_free(&g_ms.sh_oldpwd);
	ft_lstclear(&g_ms.env, free);
	ft_clear_history(&g_ms.hist.last);
	exit(exit_status);
}

void
	ft_free(char **ptr)
{
	if (*ptr)
		free(*ptr);
	*ptr = NULL;
}
