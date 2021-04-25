/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:30:29 by tnishina          #+#    #+#             */
/*   Updated: 2021/04/18 11:35:34 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int
	count_digit(long num)
{
	int	num_digit;

	num_digit = 0;
	if (num == 0)
		num_digit = 1;
	else
	{
		if (num < 0)
		{
			num_digit++;
			num *= -1;
		}
		while (num)
		{
			num_digit++;
			num = num / 10;
		}
	}
	return (num_digit);
}

static int
	create_digit(int num)
{
	int	digit;
	int	i;

	i = 1;
	digit = 1;
	while (i < num)
	{
		digit *= 10;
		i++;
	}
	return (digit);
}

char
	*ft_itoa(int n)
{
	int		num_digit;
	char	*n_string;
	long	num;
	int		i;

	num = n;
	num_digit = count_digit(num);
	n_string = (char *)malloc(sizeof(char) * (num_digit + 1));
	if (!n_string)
		return (NULL);
	i = 0;
	if (num < 0)
	{
		n_string[i] = '-';
		num *= -1;
		i++;
	}
	while (i < num_digit)
	{
		n_string[i] = num / create_digit(num_digit - i) + '0';
		num = num % create_digit(num_digit - i);
		i++;
	}
	n_string[i] = '\0';
	return (n_string);
}
