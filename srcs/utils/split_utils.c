#include "minishell_sikeda.h"

void
	ft_free_split(char ***split)
{
	size_t	i;

	i = 0;
	if (!*split)
		return ;
	while ((*split)[i])
	{
		free((*split)[i]);
		(*split)[i] = NULL;
		i++;
	}
	free(*split);
	*split = NULL;
}

char
	*ft_free_split_and_return_str(char ***split, const char *return_value)
{
	ft_free_split(split);
	return ((char *)return_value);
}

int
	ft_free_split_and_return_int(char ***split, const int return_value)
{
	ft_free_split(split);
	return (return_value);
}
