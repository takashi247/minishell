/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 10:22:53 by tnishina          #+#    #+#             */
/*   Updated: 2021/04/18 11:49:27 by sikeda           ###   ########.fr       */
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
		sub_s = ft_calloc(1, sizeof(char));
		if (!sub_s)
			return (NULL);
		return (sub_s);
	}
	i = len;
	if (len > ft_strlen(s) - start)
		i = ft_strlen(s) - start;
	sub_s = (char *)malloc(sizeof(char) * (i + 1));
	if (!sub_s)
		return (NULL);
	ft_strlcpy(sub_s, s + start, i + 1);
	return (sub_s);
}
