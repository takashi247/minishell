/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:11:32 by tnishina          #+#    #+#             */
/*   Updated: 2021/02/27 18:16:37 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*u_dst;
	unsigned char	*u_src;

	if (dst == NULL && src == NULL)
		return (NULL);
	u_dst = (unsigned char *)dst;
	u_src = (unsigned char *)src;
	while (n > 0)
	{
		*u_dst = *u_src;
		u_dst++;
		u_src++;
		n--;
	}
	return (dst);
}
