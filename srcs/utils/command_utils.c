#include "minishell_tnishina.h"

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
