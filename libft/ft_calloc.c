/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 10:02:41 by tnishina          #+#    #+#             */
/*   Updated: 2021/02/27 18:13:15 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	*ft_calloc(size_t count, size_t size)
{
	void	*res;

	if (!(res = (void *)malloc(size * count)))
		return (NULL);
	ft_bzero(res, size * count);
	return (res);
}
