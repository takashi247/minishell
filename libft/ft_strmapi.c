/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 20:44:09 by tnishina          #+#    #+#             */
/*   Updated: 2021/04/18 11:43:48 by sikeda           ###   ########.fr       */
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
	s_new = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!s_new)
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
