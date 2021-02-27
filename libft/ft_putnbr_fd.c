/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 23:11:15 by tnishina          #+#    #+#             */
/*   Updated: 2021/02/27 18:17:16 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	ft_putnbr_fd(int n, int fd)
{
	long long	num;
	char		c;

	num = n;
	if (num < 0)
	{
		ft_putchar_fd('-', fd);
		num *= -1;
	}
	if (num > 9)
		ft_putnbr_fd(num / 10, fd);
	c = num % 10 + '0';
	ft_putchar_fd(c, fd);
}
