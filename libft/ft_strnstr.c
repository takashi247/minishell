/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:58:33 by tnishina          #+#    #+#             */
/*   Updated: 2021/02/27 18:18:48 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char
	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;
	size_t	i;

	if (!needle)
		return (NULL);
	needle_len = ft_strlen(needle);
	if (needle_len == 0)
		return ((char *)haystack);
	i = 0;
	while (haystack[i] && i + needle_len <= len)
	{
		if (haystack[i] == *needle)
		{
			if (!(ft_strncmp(haystack + i, needle, needle_len)))
				return ((char *)(haystack + i));
		}
		i++;
	}
	return (NULL);
}
