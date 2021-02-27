/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 15:06:48 by tnishina          #+#    #+#             */
/*   Updated: 2021/02/27 18:18:07 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char
	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s_comb;
	size_t	size;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!(s_comb = (char *)malloc(size)))
		return (NULL);
	ft_strlcpy(s_comb, s1, size);
	ft_strlcat(s_comb, s2, size);
	return (s_comb);
}
