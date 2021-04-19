#include "test_builtin.h"

int
	main(int ac, char **av)
{
	char	**args;
	char	**args_head;
	int		i;

	if (ac < 2)
	{
		ft_put_error(strerror(EINVAL));
		return (EXIT_FAILURE);
	}
	if (test_init_minishell() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	args = (char **)malloc(sizeof(char *) * (ac + 1));
	if (!args)
		test_finalize_minishell(NULL, EXIT_FAILURE);
	i = -1;
	while (++i < ac)
		args[i] = av[i];
	args[i] = NULL;
	args_head = args;
	test_commands(args);
	test_finalize_minishell(args_head, g_status);
}
