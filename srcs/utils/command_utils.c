#include "minishell_sikeda.h"

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

char
	*ft_get_cmd_option(char *option, const char *arg)
{
	if (!option || !arg)
		return (NULL);
	if (arg[0] == '-' && arg[1] != '\0')
	{
		option[0] = '-';
		option[1] = arg[1];
		option[2] = '\0';
		return (option);
	}
	return (NULL);
}
