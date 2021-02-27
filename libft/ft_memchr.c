/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 18:58:44 by tnishina          #+#    #+#             */
/*   Updated: 2021/02/27 18:16:19 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*u_s;
	unsigned char	u_c;
	size_t			i;

	u_s = (unsigned char *)s;
	u_c = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (u_s[i] == u_c)
			return ((void*)s + i);
		i++;
	}
	return (NULL);
}
