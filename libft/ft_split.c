/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 16:05:36 by tnishina          #+#    #+#             */
/*   Updated: 2021/04/18 11:41:13 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int
	ary_size(char *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s == '\0')
			return (i);
		while (*s && *s != c)
			s++;
		i++;
	}
	return (i);
}

static char
	**free_ary(char **ary)
{
	int		i;

	i = 0;
	while (ary[i])
	{
		free(ary[i]);
		i++;
	}
	free(ary);
	return (NULL);
}

static char
	**split_ary(char **ary, char *s, char c)
{
	int		len;
	int		i;

	i = 0;
	while (1)
	{
		while (*s && *s == c)
			s++;
		if (!*s)
			break ;
		len = 0;
		while (s[len] && s[len] != c)
			len++;
		ary[i] = ft_substr(s, 0, len);
		if (!ary[i])
			return (free_ary(ary));
		i++;
		s += len;
	}
	ary[i] = NULL;
	return (ary);
}

char
	**ft_split(char const *s, char c)
{
	char	**ary;

	if (s == NULL)
		return (NULL);
	ary = (char **)malloc(sizeof(char *) * (ary_size((char *)s, c) + 1));
	if (!ary)
		return (NULL);
	return (split_ary(ary, (char *)s, c));
}
