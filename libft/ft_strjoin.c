/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 15:06:48 by tnishina          #+#    #+#             */
/*   Updated: 2021/04/18 11:42:52 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char
	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s_comb;
	size_t	size;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s1 == NULL)
		return (ft_strdup(s2));
	else if (s2 == NULL)
		return (ft_strdup(s1));
	else
	{
		size = ft_strlen(s1) + ft_strlen(s2) + 1;
		s_comb = (char *)malloc(size);
		if (!s_comb)
			return (NULL);
		ft_strlcpy(s_comb, s1, size);
		ft_strlcat(s_comb, s2, size);
	}
	return (s_comb);
}
