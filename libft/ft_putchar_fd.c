/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 22:11:02 by tnishina          #+#    #+#             */
/*   Updated: 2021/02/27 18:16:57 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	ft_putchar_fd(char c, int fd)
{
	unsigned char	uc;
	unsigned char	chr;

	uc = (unsigned char)c;
	if (uc <= 0x7F)
		write(fd, &c, 1);
	else
	{
		chr = (uc >> 6) ^ 0xC0;
		write(fd, &chr, 1);
		chr = (uc & 0x3F) ^ 0x80;
		write(fd, &chr, 1);
	}
}
