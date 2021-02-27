/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 22:51:49 by tnishina          #+#    #+#             */
/*   Updated: 2021/02/27 18:15:24 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*prev;
	t_list	*current;

	if (!lst || !del)
		return ;
	current = *lst;
	while (current)
	{
		prev = current;
		current = current->next;
		ft_lstdelone(prev, del);
	}
	*lst = NULL;
}
