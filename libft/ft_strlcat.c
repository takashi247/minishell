/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 09:42:49 by tnishina          #+#    #+#             */
/*   Updated: 2021/02/27 18:18:13 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t
	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len;
	size_t	max;
	size_t	i;

	if (dstsize <= ft_strlen(dst))
		len = ft_strlen(src) + dstsize;
	else
	{
		len = ft_strlen(src) + ft_strlen(dst);
		i = ft_strlen(dst);
		max = dstsize - 1;
		while (*src && i < max)
			dst[i++] = *src++;
		dst[i] = '\0';
	}
	return (len);
}
