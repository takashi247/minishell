#include "minishell_sikeda.h"

void
	*ft_realloc(void *original, size_t size, size_t original_size)
{
	void	*new;

	if (!original)
		return (malloc(size));
	new = malloc(size);
	if (new)
	{
		if (original_size < size)
			ft_memcpy(new, original, original_size);
		else
			ft_memcpy(new, original, size);
	}
	free(original);
	return (new);
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

int
	ft_isspace(char c)
{
	return (c == ' ' || (9 <= c && c <= 13));
}

int
	ft_isnumeric(char *s)
{
	if (!s || *s == '\0')
		return (0);
	if (*s == '+' || *s == '-')
		s++;
	if (!ft_isdigit(*s))
		return (0);
	while (*s)
	{
		if (!ft_isdigit(*s++))
			return (0);
	}
	return (1);
}

void
	ft_free(char **ptr)
{
	if (*ptr)
		free(*ptr);
	*ptr = NULL;
}
