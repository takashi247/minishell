#include "minishell.h"

static void
	check_command_dir(char *command, char *command_dir)
{
	struct stat	buf;

	if (stat(command_dir, &buf) != 0)
	{
		ft_put_cmderror(command, strerror(errno));
		g_ms.status = STATUS_COMMAND_NOT_FOUND;
		ft_exit_n_free_g_vars(g_ms.status);
	}
	else if (!(buf.st_mode & S_IFDIR))
	{
		ft_put_cmderror(command, IS_NOT_DIR_ERR_MSG);
		g_ms.status = STATUS_CANNOT_EXECUTE;
		ft_exit_n_free_g_vars(g_ms.status);
	}
}

void
	ft_execute_w_environ(char **argv)
{
	char	**envp;

	envp = ft_convert_list(g_ms.env);
	if (!envp)
		ft_exit_n_free_g_vars(STATUS_GENERAL_ERR);
	execve(argv[0], argv, envp);
	ft_free_split(&envp);
}

static void
	execute_path_command(char **argv)
{
	struct stat	buf;

	if (stat(argv[0], &buf) != 0)
	{
		ft_put_cmderror(argv[0], strerror(errno));
		g_ms.status = STATUS_COMMAND_NOT_FOUND;
		ft_exit_n_free_g_vars(g_ms.status);
	}
	else if (buf.st_mode & S_IFDIR)
	{
		ft_put_cmderror(argv[0], IS_DIR_ERROR_MSG);
		g_ms.status = STATUS_CANNOT_EXECUTE;
		ft_exit_n_free_g_vars(g_ms.status);
	}
	else if (!(buf.st_mode & S_IRUSR) || !(buf.st_mode & S_IXUSR))
	{
		ft_put_cmderror(argv[0], PERMISSION_ERR_MSG);
		g_ms.status = STATUS_CANNOT_EXECUTE;
		ft_exit_n_free_g_vars(g_ms.status);
	}
	else
		ft_execute_w_environ(argv);
}

void
	ft_do_path_command(char **argv, char **command_dir)
{
	if (*command_dir && **command_dir)
		check_command_dir(argv[0], *command_dir);
	ft_free(command_dir);
	if (!argv[0][0])
	{
		ft_put_cmderror(argv[0], COMMAND_NOT_FOUND_ERR_MSG);
		g_ms.status = STATUS_COMMAND_NOT_FOUND;
	}
	else
		execute_path_command(argv);
	ft_exit_n_free_g_vars(g_ms.status);
}
