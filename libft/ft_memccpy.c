/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:22:59 by tnishina          #+#    #+#             */
/*   Updated: 2021/02/27 18:16:12 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*u_dst;
	unsigned char	*u_src;
	unsigned char	u_c;
	size_t			i;

	u_dst = (unsigned char *)dst;
	u_src = (unsigned char *)src;
	u_c = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		u_dst[i] = *u_src;
		i++;
		if (*u_src == u_c)
			return (dst + i);
		u_src++;
	}
	return (NULL);
}
