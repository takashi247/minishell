#include "minishell_sikeda.h"

char
	*ft_getenv(const char *name)
{
	t_list	*envptr;
	size_t	len;
	char	*current;

	if (!g_env || !*name)
		return (NULL);
	len = ft_strlen(name);
	envptr = g_env;
	while (envptr)
	{
		current = envptr->content;
		if (!ft_strncmp(name, current, len)
		&& (current[len] == '=' || current[len] == '\0'))
			return (current + len + 1);
		envptr = envptr->next;
	}
	return (NULL);
}

static void
	delone_env(char *str)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(str);
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			str[i] = '\0';
			break ;
		}
		i++;
	}
	if (ft_getenv(str))
		ft_unsetenv(str);
	if (i != len)
		str[i] = '=';
}

int
	ft_setenv(char *str)
{
	t_list	*new;
	char	*cpy;

	if (!g_env || !str || !*str)
		return (UTIL_ERROR);
	delone_env(str);
	if (!(cpy = ft_strdup(str)) || !(new = ft_lstnew(cpy)))
	{
		cpy ? FREE(cpy) : cpy;
		return (UTIL_ERROR);
	}
	ft_lstadd_back(&g_env, new);
	return (UTIL_SUCCESS);
}

int
	ft_setenv_sep(char *name, char *value)
{
	char	*equal_value;
	char	*env_str;
	int		ret;

	if (!g_env || !name)
		return (UTIL_ERROR);
	equal_value = NULL;
	if (value && !(equal_value = ft_strjoin("=", value)))
		return (UTIL_ERROR);
	if (equal_value)
		env_str = ft_strjoin(name, equal_value);
	else
		env_str = ft_strdup(name);
	ret = UTIL_ERROR;
	if (env_str)
		ret = ft_setenv(env_str);
	FREE(equal_value);
	FREE(env_str);
	return (ret);
}

int
	ft_unsetenv(const char *name)
{
	t_list	*envptr;
	t_list	*prev;
	size_t	len;

	if (!g_env || !name || !*name)
		return (UTIL_ERROR);
	envptr = g_env;
	prev = NULL;
	len = ft_strlen(name);
	while (envptr)
	{
		if (!ft_strncmp(name, envptr->content, len)
		&& (((char*)envptr->content)[len] == '='
		|| ((char*)envptr->content)[len] == '\0'))
		{
			if (prev)
				prev->next = envptr->next;
			else
				g_env = envptr->next;
			ft_lstdelone(envptr, free);
			return (UTIL_SUCCESS);
		}
		prev = envptr;
		envptr = envptr->next;
	}
	return (UTIL_ERROR);
}

static int
	change_first_target_to_char(char *str, char target, char c)
{
	if (!str)
		return (UTIL_ERROR);
	while (*str)
	{
		if (*str == target)
		{
			*str = c;
			return (UTIL_SUCCESS);
		}
		str++;
	}
	if (*str == target)
	{
		*str = c;
		return (UTIL_SUCCESS);
	}
	return (UTIL_ERROR);
}

static void
	env_merge_loop(t_list **left, t_list **right, t_list **next)
{
	int	l_flg;
	int	r_flg;
	int	comp;

	l_flg = change_first_target_to_char((*left)->content, '=', '\0');
	r_flg = change_first_target_to_char((*right)->content, '=', '\0');
	comp = ft_strcmp((*left)->content, (*right)->content);
	if (l_flg == UTIL_SUCCESS)
		change_first_target_to_char((*left)->content, '\0', '=');
	if (r_flg == UTIL_SUCCESS)
		change_first_target_to_char((*right)->content, '\0', '=');
	if (comp <= 0)
	{
		(*next)->next = *left;
		*next = (*next)->next;
		*left = (*left)->next;
	}
	else
	{
		(*next)->next = *right;
		*next = (*next)->next;
		*right = (*right)->next;
	}
}

static t_list
	*env_merge(t_list *left, t_list *right)
{
	t_list	head;
	t_list	*next;

	next = &head;
	while (left && right)
		env_merge_loop(&left, &right, &next);
	if (!left)
		next->next = right;
	else
		next->next = left;
	return (head.next);
}

static t_list
	*env_merge_sort_rec(t_list *lst)
{
	t_list	*left;
	t_list	*right;
	t_list	*right_head;

	if (!lst || !lst->next)
		return (lst);
	left = lst;
	right = lst->next;
	if (right)
		right = right->next;
	while (right)
	{
		left = left->next;
		right = right->next;
		if (right)
			right = right->next;
	}
	right_head = left->next;
	left->next = NULL;
	return (env_merge(env_merge_sort_rec(lst), env_merge_sort_rec(right_head)));
}

void
	ft_envsort(t_list **lst)
{
	if (!lst)
		return ;
	*lst = env_merge_sort_rec(*lst);
}

void
	ft_clear_copied_env(t_list **cpy)
{
	t_list	*tmp;

	if (!cpy)
		return ;
	while (*cpy)
	{
		tmp = (*cpy)->next;
		FREE(*cpy);
		*cpy = tmp;
	}
}

t_list
	*ft_copy_env(void)
{
	t_list	*copy;
	t_list	*envptr;
	t_list	*current;

	copy = NULL;
	envptr = g_env;
	while (envptr)
	{
		if (!(current = ft_lstnew(envptr->content)))
		{
			ft_clear_copied_env(&copy);
			return (NULL);
		}
		ft_lstadd_back(&copy, current);
		envptr = envptr->next;
	}
	return (copy);
}
