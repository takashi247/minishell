#include "minishell_tnishina.h"
#include "minishell_sikeda.h"
#include "libft.h"

static char
	*get_command_dir(char *command)
{
	int		len;
	char	*command_dir;

	if (!command)
		return (NULL);
	len = ft_strlen(command);
	while (len && command[--len] != '/')
		continue ;
	command_dir = ft_substr(command, 0, len);
	return (command_dir);
}

void
	ft_do_command(t_command *c)
{
	char		**argv;
	char		*path_env;
	char		*command_dir;

	if (!c)
		ft_exit_n_free_g_vars(STATUS_GENERAL_ERR);
	if (!c->args)
		ft_exit_n_free_g_vars(g_status);
	argv = ft_convert_list(c->args);
	if (!argv)
		ft_exit_n_free_g_vars(STATUS_GENERAL_ERR);
	path_env = ft_getenv("PATH");
	command_dir = get_command_dir(argv[0]);
	if (!command_dir)
		ft_exit_n_free_g_vars(STATUS_GENERAL_ERR);
	if (argv[0][0] == '/' || argv[0][0] == '.' || !path_env
		|| !*path_env || *command_dir)
		ft_do_path_command(argv, command_dir);
	else
	{
		ft_free(&command_dir);
		ft_do_nonpath_command(&path_env, &argv);
	}
}
