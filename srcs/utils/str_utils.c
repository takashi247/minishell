#include "minishell_tnishina.h"

char
	*ft_strndup_append_null(const char *s, size_t n)
{
	char	*p;
	size_t	i;

	if (!s)
		return (NULL);
	if (n == SIZE_MAX)
		return (NULL);
	p = (char *)malloc(sizeof(char) * (n + 1));
	if (!p)
		return (NULL);
	i = 0;
	while (i < n && s[i])
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

int
	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 || *s2)
	{
		if (*s1 != *s2)
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		s1++;
		s2++;
	}
	return (0);
}
