/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 10:22:53 by tnishina          #+#    #+#             */
/*   Updated: 2021/02/27 18:19:15 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char
	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_s;
	size_t	i;

	if (s == NULL || ft_strlen(s) <= start || len == 0)
	{
		if (!(sub_s = ft_calloc(1, sizeof(char))))
			return (NULL);
		return (sub_s);
	}
	i = (len > ft_strlen(s) - start) ? (ft_strlen(s) - start) : len;
	if (!(sub_s = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	ft_strlcpy(sub_s, s + start, i + 1);
	return (sub_s);
}
