/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnishina <tnishina@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 08:02:41 by tnishina          #+#    #+#             */
/*   Updated: 2021/02/27 18:12:46 by tnishina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int
	check_overflow(long long res, char c)
{
	if (res > LONG_MAX / 10 ||
			(res == LONG_MAX / 10 && c - '0' > LONG_MAX % 10))
		return (-1);
	if (res < LONG_MIN / 10 ||
			(res == LONG_MIN / 10 && c - '0' > LONG_MIN % 10 * -1))
		return (0);
	return (1);
}

int
	ft_atoi(const char *str)
{
	long long	res;
	int			sign;

	res = 0;
	sign = 1;
	while (*str == '\t' || *str == '\n' || *str == '\v' ||
			*str == '\f' || *str == '\r' || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str == '0')
		str++;
	while (ft_isdigit(*str) && check_overflow(res * sign, *str) == 1)
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	if (check_overflow(res * sign, *str) != 1 && ft_isdigit(*str))
		return (check_overflow(res * sign, *str));
	return ((int)res * sign);
}
