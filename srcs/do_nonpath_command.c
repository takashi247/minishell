#include "minishell_tnishina.h"
#include "minishell_sikeda.h"
#include "libft.h"

static void
	set_dir_error(char *command)
{
	ft_free(&g_err_arg);
	ft_free(&g_err_msg);
	g_err_arg = ft_strdup(command);
	g_err_msg = ft_strdup(IS_DIR_ERROR_MSG);
	g_status = STATUS_COMMAND_NOT_FOUND;
}

static void
	set_permission_error(char *command)
{
	ft_free(&g_err_arg);
	ft_free(&g_err_msg);
	g_err_arg = ft_strdup(command);
	g_err_msg = ft_strdup(PERMISSION_ERR_MSG);
	g_status = STATUS_CANNOT_EXECUTE;
}

static void
	execute_command_loop(char *c, char *path, char **argv, char **environ)
{
	char		*tmp;
	struct stat	buf;

	tmp = ft_strjoin(path, "/");
	if (tmp)
		argv[0] = ft_strjoin(tmp, c);
	if (!tmp || !argv[0])
		ft_exit_n_free_g_vars(STATUS_GENERAL_ERR);
	ft_free(&tmp);
	if (stat(argv[0], &buf) == 0)
	{
		if (buf.st_mode & S_IFDIR)
			set_dir_error(argv[0]);
		else if (!(buf.st_mode & S_IRUSR) || !(buf.st_mode & S_IXUSR))
			set_permission_error(argv[0]);
		else
			execve(argv[0], argv, environ);
	}
}

void
	ft_do_nonpath_command(char **path_env, char ***argv, char **environ)
{
	char		**paths;
	char		**head;
	char		*command;

	*path_env = ft_get_pathenv(*path_env);
	paths = ft_split(*path_env, ':');
	command = ft_strdup((*argv)[0]);
	if (!(*path_env) || !paths || !command)
		ft_exit_n_free_g_vars(STATUS_GENERAL_ERR);
	head = paths;
	while (*paths)
	{
		ft_free(&((*argv)[0]));
		execute_command_loop(command, *paths, *argv, environ);
		paths++;
	}
	ft_do_command_err(command);
	ft_free(path_env);
	ft_free_split(argv);
	ft_free_split(&head);
	ft_exit_n_free_g_vars(g_status);
}
