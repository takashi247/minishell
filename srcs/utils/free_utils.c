#include "minishell_tnishina.h"

void
	ft_clear_argv(char ***argv)
{
	char	**head;

	if (*argv)
		head = *argv;
	while (**argv)
	{
		ft_free(*argv);
		(*argv)++;
	}
	free(head);
	head = NULL;
}

void
	ft_free(char **ptr)
{
	if (*ptr)
		free(*ptr);
	*ptr = NULL;
}

int
	ft_free_n_return(char **ptr, int return_value)
{
	if (ptr)
		ft_free(ptr);
	return (return_value);
}
