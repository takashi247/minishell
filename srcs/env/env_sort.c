#include "minishell.h"

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
