#include "minishell_tnishina.h"
#include "minishell_sikeda.h"
#include "libft.h"

static void
	check_command_dir(char *command, char *command_dir)
{
	struct stat	buf;

	if (stat(command_dir, &buf) != 0)
	{
		ft_put_cmderror(command, strerror(errno));
		g_status = STATUS_COMMAND_NOT_FOUND;
		ft_exit_n_free_g_vars(g_status);
	}
	else if (!(buf.st_mode & S_IFDIR))
	{
		ft_put_cmderror(command, IS_NOT_DIR_ERR_MSG);
		g_status = STATUS_CANNOT_EXECUTE;
		ft_exit_n_free_g_vars(g_status);
	}
}

static void
	execute_path_command(char **argv, char **environ)
{
	struct stat	buf;

	if (stat(argv[0], &buf) != 0)
	{
		ft_put_cmderror(argv[0], strerror(errno));
		g_status = STATUS_COMMAND_NOT_FOUND;
		ft_exit_n_free_g_vars(g_status);
	}
	else if (buf.st_mode & S_IFDIR)
	{
		ft_put_cmderror(argv[0], IS_DIR_ERROR_MSG);
		g_status = STATUS_CANNOT_EXECUTE;
		ft_exit_n_free_g_vars(g_status);
	}
	else if (!(buf.st_mode & S_IRUSR) || !(buf.st_mode & S_IXUSR))
	{
		ft_put_cmderror(argv[0], PERMISSION_ERR_MSG);
		g_status = STATUS_CANNOT_EXECUTE;
		ft_exit_n_free_g_vars(g_status);
	}
	else
		execve(argv[0], argv, environ);
}

void
	ft_do_path_command(char **argv, char *command_dir, char **environ)
{
	if (*command_dir)
		check_command_dir(argv[0], command_dir);
	ft_free(&command_dir);
	execute_path_command(argv, environ);
	ft_exit_n_free_g_vars(g_status);
}
