/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 15:26:48 by tnishina          #+#    #+#             */
/*   Updated: 2021/04/18 11:44:31 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int
	is_set(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char
	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*s_trim;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return ((char *)s1);
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && is_set(s1[start], set))
		start++;
	while (end > start && is_set(s1[end - 1], set))
		end--;
	s_trim = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!s_trim)
		return (NULL);
	if (start < end)
		s_trim = ft_memcpy(s_trim, s1 + start, sizeof(char) * (end - start));
	s_trim[end - start] = '\0';
	return (s_trim);
}
