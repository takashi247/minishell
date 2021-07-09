#include "minishell.h"

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

char
	**ft_convert_list(t_list *l)
{
	char	**argv;
	char	**head;

	if (!l)
		return (NULL);
	argv = (char **)malloc(sizeof(char *) * (ft_lstsize(l) + 1));
	if (!argv)
		return (NULL);
	head = argv;
	ft_memset(argv, 0, sizeof(char *) * (ft_lstsize(l) + 1));
	while (l)
	{
		*argv = ft_strdup((char *)(l->content));
		if (!*argv)
		{
			ft_clear_argv(&head);
			ft_put_error(strerror(errno));
			return (NULL);
		}
		argv++;
		l = l->next;
	}
	*argv = NULL;
	return (head);
}
