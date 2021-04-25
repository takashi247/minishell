/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 09:40:12 by tnishina          #+#    #+#             */
/*   Updated: 2021/04/18 11:42:24 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char
	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*dup;

	i = sizeof(char) * (ft_strlen(s1) + 1);
	dup = (char *)malloc(i);
	if (!dup)
		return (NULL);
	ft_memcpy(dup, s1, i);
	return (dup);
}
