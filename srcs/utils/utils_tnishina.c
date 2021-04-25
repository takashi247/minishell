#include "minishell_tnishina.h"
#include "minishell_sikeda.h"
#include "libft.h"

char
	**ft_convert_list(t_list *l)
{
	char	**argv;
	char	**head;

	if (!l)
		return (NULL);
	argv = (char** )malloc(sizeof(char* ) * (ft_lstsize(l) + 1));
	if (!argv)
		return (NULL);
	head = argv;
	ft_memset(argv, 0, sizeof(char* ) * (ft_lstsize(l) + 1));
	while (l)
	{
		*argv = ft_strdup((char* )(l->content));
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