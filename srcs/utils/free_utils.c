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
