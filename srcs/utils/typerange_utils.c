#include "minishell_tnishina.h"

int
	ft_isover_intrange(char *s)
{
	uint64_t	num;
	int			is_minus;

	is_minus = 0;
	while (ft_isspace(*s))
		s++;
	if (*s == '-')
		is_minus = 1;
	if (*s == '+' || *s == '-')
		s++;
	num = 0;
	while (ft_isdigit(*s))
	{
		num = num * 10 + *s - '0';
		if (is_minus && (int64_t)__INT_MAX__ + 1 < num)
			return (-1);
		else if (!is_minus && (uint64_t)__INT_MAX__ < num)
			return (1);
		s++;
	}
	return (0);
}

int
	ft_isover_llrange(char *s)
{
	uint64_t	num;
	int			is_minus;

	while (ft_isspace(*s))
		s++;
	is_minus = 0;
	if (*s == '-')
		is_minus = 1;
	if (*s == '+' || *s == '-')
		s++;
	num = 0;
	while (ft_isdigit(*s))
	{
		num = num * 10 + *s - '0';
		if (is_minus && (uint64_t)__LONG_LONG_MAX__ + 1 < num)
			return (-1);
		else if (!is_minus && (uint64_t)__LONG_LONG_MAX__ < num)
			return (1);
		s++;
	}
	return (0);
}
