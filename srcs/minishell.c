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
	do_command(t_command *c, char **environ)
{
	char		**argv;
	char		*path_env;
	char		*command_dir;

	if (!c || !environ)
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
	if (argv[0][0] == '/' || argv[0][0] == '.' || !path_env || !*path_env || *command_dir)
		ft_do_path_command(argv, command_dir, environ);
	else
	{
		ft_free(&command_dir);
		ft_do_nonpath_command(&path_env, &argv, environ);
	}
}

static t_bool
	is_pipe(t_command *c)
{
	if (!ft_strncmp(c->op, "|", ft_strlen("|") + 1))
		return (TRUE);
	else
		return (FALSE);
}

static int
	do_builtin_cmd(char **argv)
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
		res = ft_exit(argv);
	return (res);
}

int
	ft_execute_builtin(t_command *c)
{
	char	**argv;
	int		res;
	int		std_fds[3];

	res = KEEP_RUNNING;
	ft_save_fds(std_fds);
	if (ft_set_redirection(c->redirects, std_fds) == FALSE)
		return (STOP);
	if (c->args)
	{
		argv = ft_convert_list(c->args);
		if (!argv)
		{
			g_status = 1;
			return (STOP);
		}
		res = do_builtin_cmd(argv);
		ft_clear_argv(&argv);
	}
	ft_restore_fds(std_fds);
	return (res);
}

static t_bool
	is_builtin(t_command *c)
{
	if (c->args
		&& (!ft_strcmp((char* )(c->args->content), "echo")
		|| !ft_strcmp((char* )(c->args->content), "cd")
		|| !ft_strcmp((char* )(c->args->content), "pwd")
		|| !ft_strcmp((char* )(c->args->content), "export")
		|| !ft_strcmp((char* )(c->args->content), "unset")
		|| !ft_strcmp((char* )(c->args->content), "env")
		|| !ft_strcmp((char* )(c->args->content), "exit")))
		return (TRUE);
	else
		return (FALSE);
}

static void
	dup_to_stdfd(t_bool pipe_flag[2], int lastpipe[2], int newpipe[2])
{
	if (pipe_flag[1])
	{
		close(lastpipe[1]);
		if (dup2(lastpipe[0], STDIN_FILENO) < 0)
			ft_exit_n_free_g_vars(STATUS_GENERAL_ERR);
		close(lastpipe[0]);
	}
	if (pipe_flag[0])
	{
		close(newpipe[0]);
		if (dup2(newpipe[1], STDOUT_FILENO) < 0)
			ft_exit_n_free_g_vars(STATUS_GENERAL_ERR);
		close(newpipe[1]);
	}
}

static void
	execute_child(t_command *c, int std_fds[3], char **environ)
{
	if (is_builtin(c))
	{
		ft_execute_builtin(c);
		ft_exit_n_free_g_vars(g_status);
	}
	else
	{
		ft_save_fds(std_fds);
		if (ft_set_redirection(c->redirects, std_fds))
			do_command(c, environ);
		else
			ft_exit_n_free_g_vars(g_status);
	}
}

static void
	update_pipes(t_bool pipe_flag[2], int lastpipe[2], int newpipe[2])
{
	if (pipe_flag[1])
	{
		close(lastpipe[0]);
		close(lastpipe[1]);
	}
	if (pipe_flag[0])
	{
		lastpipe[0] = newpipe[0];
		lastpipe[1] = newpipe[1];
	}
}

static void
	start_command(t_command *c, t_bool pipe_flag[2], int lastpipe[2], char **environ)
{
	pid_t	pid;
	int		newpipe[2];
	int		std_fds[3];

	pipe_flag[0] = is_pipe(c);
	if (c->args || c->redirects)
	{
		if (pipe_flag[0])
			pipe(newpipe);
		pid = fork();
		if (pid == 0)
		{
			dup_to_stdfd(pipe_flag, lastpipe, newpipe);
			execute_child(c, std_fds, environ);
		}
		update_pipes(pipe_flag, lastpipe, newpipe);
		c->pid = pid;
	}
	pipe_flag[1] = is_pipe(c);
}

/*
** pipe_flag[0]: a flag to denote if a command's operator is a pipe
** pipe_flag[1]: a flag to denote if a command is piped from the previous one
*/

t_command
	*ft_execute_pipeline(t_command *c, char **environ)
{
	t_bool	pipe_flag[2];
	int		lastpipe[2];
	int		res;

	pipe_flag[1] = FALSE;
	ft_memset(lastpipe, -1, sizeof(lastpipe));
	while (c && res != REDIRECT_DELETED)
	{
		res = ft_expand_env_var(c);
		if (res == COMPLETED)
		{
			start_command(c, pipe_flag, lastpipe, environ);
			if (pipe_flag[1])
				c = c->next;
			else
				break ;
		}
		else if (res == REDIRECT_DELETED)
			c = c->next;
		else
			return (NULL);
	}
	return (c);
}

static t_bool
	is_end_with_escape(char *line)
{
	int	len;
	int	count;

	if (!line || !(*line))
		return (FALSE);
	len = ft_strlen(line);
	count = 0;
	while (line[len - 1] == '\\')
	{
		count++;
		len--;
	}
	if (count % 2 != 0)
		return (TRUE);
	else
		return (FALSE);
}

static void
	add_final_char(char **trimmed, char *line)
{
	char	*final;
	char	*tmp;
	size_t	size;
	size_t	len;

	if (*trimmed && line)
	{
		tmp = *trimmed;
		size = ft_strlen(*trimmed) + 2;
		*trimmed = (char *)malloc(sizeof(char) * size);
		if ((*trimmed))
		{
			ft_strlcpy(*trimmed, tmp, size);
			ft_free(&tmp);
			final = (char *)malloc(sizeof(char) * 2);
			if (final)
			{
				len = ft_strlen(line);
				while (line[len] != '\\')
					final[0] = line[len--];
				final[1] = '\0';
				ft_strlcat(*trimmed, final, size);
			}
			else
				ft_free(trimmed);
		}
		else
			ft_free(&tmp);
	}
}

static t_bool
	wait_pipeline(pid_t pid)
{
	int		term_status;

	g_latest_pid = pid;
	if (waitpid(pid, &term_status, 0) < 0)
		return (FALSE);
	if (WIFEXITED(term_status))
		g_status = WEXITSTATUS(term_status);
	while (wait(NULL) > 0) ;
	return (TRUE);
}

int
	main(void)
{
	char		*line;
	char		*trimmed;
	extern char	**environ;
	t_list		*tokens;
	t_command	*head;
	t_command	*commands;
	int			res;
	int			expand_res;

	if (init_minishell() == UTIL_ERROR)
		return (EXIT_FAILURE);
	line = NULL;
	trimmed = NULL;
	head = NULL;
	while (1)
	{
		ft_sig_prior();
		res = ft_get_line(&line);
		if (res == GNL_ERROR)
		{
			g_status = STATUS_GENERAL_ERR;
			break ;
		}
		ft_sig_post();
		if (is_end_with_escape(line))
			ft_put_cmderror("\\", MULTILINE_ERROR_MSG);
		else
		{
			res = ft_add_space(&line);
			trimmed = ft_strtrim(line, " \t");
			if (is_end_with_escape(trimmed))
				add_final_char(&trimmed, line);
			if (res != KEEP_RUNNING || !trimmed
				|| ft_make_token(&tokens, trimmed, ft_is_delimiter_or_quote) != COMPLETED
				|| ft_make_command(&commands, tokens) != COMPLETED)
			{
				ft_free(&line);
				ft_free(&trimmed);
				ft_lstclear(&tokens, free);
				ft_exit_n_free_g_vars(STATUS_GENERAL_ERR);
			}
			res = KEEP_RUNNING;
			head = commands;
			while (commands)
			{
				expand_res = ft_expand_env_var(commands);
				if (expand_res == FAILED)
					break ;
				else if (expand_res == COMPLETED)
				{
					if (commands->args || commands->redirects)
					{
						if (is_builtin(commands) && !is_pipe(commands))
						{
							res = ft_execute_builtin(commands);
							if (res != KEEP_RUNNING)
								break ;
							commands = commands->next;
							continue ;
						}
						commands = ft_execute_pipeline(commands, environ);
						if (!commands || !wait_pipeline(commands->pid))
							ft_exit_n_free_g_vars(STATUS_GENERAL_ERR);
					}
				}
				commands = commands->next;
			}
			if (res == EXIT || res == EXIT_NON_NUMERIC)
			{
				if (res == EXIT)
					ft_putstr_fd(EXIT_PROMPT, STDERR_FILENO);
				break;
			}
		}
		ft_free(&line);
		ft_free(&trimmed);
		ft_clear_commands(&head);
	}
	ft_free(&line);
	ft_free(&trimmed);
	ft_clear_commands(&head);
	ft_exit_n_free_g_vars(g_status);
}
