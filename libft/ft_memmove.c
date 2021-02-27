/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:47:54 by tnishina          #+#    #+#             */
/*   Updated: 2021/02/27 18:16:43 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*u_dst;
	unsigned char	*u_src;
	size_t			i;

	if (dst == NULL && src == NULL)
		return (NULL);
	u_dst = (unsigned char *)dst;
	u_src = (unsigned char *)src;
	i = 0;
	if (len == 0 || u_dst == u_src)
		return (dst);
	if (u_src < u_dst)
	{
		while (len-- > 0)
			u_dst[len] = u_src[len];
	}
	else
	{
		while (i < len)
		{
			u_dst[i] = u_src[i];
			i++;
		}
	}
	return (dst);
}
