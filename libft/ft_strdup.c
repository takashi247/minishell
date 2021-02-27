/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 09:40:12 by tnishina          #+#    #+#             */
/*   Updated: 2021/02/27 18:18:01 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char
	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*dup;

	i = sizeof(char) * (ft_strlen(s1) + 1);
	if (!(dup = (char *)malloc(i)))
		return (NULL);
	ft_memcpy(dup, s1, i);
	return (dup);
}
