#include "minishell_tnishina.h"

#ifdef TOKENTEST
int
	main(int ac, char **av)
{
	char		*line;
	extern char	**environ;
	t_list		*tokens;
	t_list		*head;

	if (ft_init_env() == STOP)
		return (EXIT_FAILURE);
	if (ac == 1)
	{
		ft_putstr_fd(PROMPT, STDOUT_FILENO);
		while (get_next_line(STDIN_FILENO, &line) == 1 &&
			(ft_strncmp(line, "exit", 5)) &&
			(ft_make_token(&tokens, line, ft_is_delimiter_or_quote) == COMPLETED))
		{
			head = tokens;
			while (tokens)
			{
				ft_putstr_fd("[", STDOUT_FILENO);
				ft_putstr_fd(tokens->content, STDOUT_FILENO);
				ft_putstr_fd("]\n", STDOUT_FILENO);
				tokens = tokens->next;
			}
			ft_free(&line);
			ft_lstclear(&head, free);
			ft_putstr_fd(PROMPT, STDOUT_FILENO);
		}
		ft_free(&line);
		get_next_line(STDIN_FILENO, NULL);
		ft_putstr_fd(EXIT_PROMPT, STDOUT_FILENO);
	}
	else
	{
		if ((ft_make_token(&tokens, av[1], ft_is_delimiter_or_quote)) == COMPLETED)
		{
			head = tokens;
			while (tokens)
			{
				ft_putstr_fd("[", STDOUT_FILENO);
				ft_putstr_fd(tokens->content, STDOUT_FILENO);
				ft_putstr_fd("]\n", STDOUT_FILENO);
				tokens = tokens->next;
			}
			ft_lstclear(&head, free);
		}
	}
	ft_free(&g_pwd);
	ft_lstclear(&g_env, free);
	exit(g_status);
}
#endif
