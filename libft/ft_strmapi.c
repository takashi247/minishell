/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 20:44:09 by tnishina          #+#    #+#             */
/*   Updated: 2021/02/27 18:18:32 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char
	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*s_new;
	unsigned int	i;

	if (s == NULL || f == NULL)
		return (NULL);
	if (!(s_new = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (NULL);
	i = 0;
	while (s[i])
	{
		s_new[i] = (*f)(i, (char)s[i]);
		i++;
	}
	s_new[i] = '\0';
	return (s_new);
}
