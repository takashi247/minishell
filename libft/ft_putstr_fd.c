/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 23:05:53 by tnishina          #+#    #+#             */
/*   Updated: 2021/02/27 18:17:24 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	if (s == NULL)
		return ;
	len = ft_strlen(s);
	write(fd, s, len);
}
