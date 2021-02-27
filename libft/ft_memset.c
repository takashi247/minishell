/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:32:26 by tnishina          #+#    #+#             */
/*   Updated: 2021/02/27 18:16:51 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	uc;
	unsigned char	*ub;

	uc = (unsigned char)c;
	ub = (unsigned char *)b;
	while (len > 0)
	{
		*ub = uc;
		ub++;
		len--;
	}
	return (b);
}
