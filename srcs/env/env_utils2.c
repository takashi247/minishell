#include "minishell.h"

char
	*ft_extract_envname_from_str(const char *str)
{
	char	*name;
	char	*ret;
	size_t	len;

	len = 0;
	while (str[len] && str[len] != '=')
		len++;
	name = (char *)malloc(sizeof(char) * (len + 1));
	if (!name)
		return (NULL);
	ret = name;
	while (*str && *str != '=')
		*name++ = *str++;
	*name = '\0';
	return (ret);
}

char
	*ft_extract_envvalue_from_str(const char *str)
{
	char	*value;
	char	*ret;
	size_t	len;

	while (*str && *str != '=')
		str++;
	if (*str == '=')
		str++;
	len = 0;
	while (str[len])
		len++;
	value = (char *)malloc(sizeof(char) * (len + 1));
	if (!value)
		return (NULL);
	ret = value;
	while (*str)
		*value++ = *str++;
	*value = '\0';
	return (ret);
}
