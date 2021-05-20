#include "minishell_tnishina.h"
#include "libft.h"

static int
	do_builtin_cmd(t_bool is_pipe, char **argv)
{
	int	res;

	if (!ft_strcmp(argv[0], "echo"))
		res = ft_echo(argv);
	else if (!ft_strcmp(argv[0], "cd"))
		res = ft_cd(argv);
	else if (!ft_strcmp(argv[0], "pwd"))
		res = ft_pwd(argv);
	else if (!ft_strcmp(argv[0], "export"))
		res = ft_export(argv);
	else if (!ft_strcmp(argv[0], "unset"))
		res = ft_unset(argv);
	else if (!ft_strcmp(argv[0], "env"))
		res = ft_env(argv);
	else
	{
		if (!is_pipe)
			ft_putstr_fd(EXIT_PROMPT, STDERR_FILENO);
		res = ft_exit(argv);
	}
	return (res);
}

int
	ft_execute_builtin(t_bool is_pipe, t_command *c)
{
	char	**argv;
	int		res;
	int		std_fds[3];

	res = KEEP_RUNNING;
	ft_save_fds(c, std_fds);
	if (ft_set_redirection(c->redirects, std_fds) == FALSE)
		return (STOP);
	if (c->args)
	{
		argv = ft_convert_list(c->args);
		if (!argv)
		{
			g_ms.status = 1;
			return (STOP);
		}
		res = do_builtin_cmd(is_pipe, argv);
		ft_clear_argv(&argv);
	}
	ft_restore_fds(c, std_fds);
	return (res);
}
