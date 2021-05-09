#include "minishell_tnishina.h"
#include "minishell_sikeda.h"
#include "libft.h"

int
	exit_with_error(void)
{
	ft_put_error(strerror(errno));
	exit(g_status);
}

static char
	*get_pathenv(char *s)
{
	int		i;
	char*	path_env;
	char*	tmp;
	char*	front;
	char*	back;
	char*	pwd;

	if (!s)
		return (NULL);
	path_env = ft_strdup(s);
	if (!path_env)
		exit(STATUS_GENERAL_ERR);
	tmp = NULL;
	pwd = ".";
	i = 0;
	while (path_env[i])
	{
		if (!i && path_env[i] == ':')
		{
			tmp = path_env;
			path_env = ft_strjoin(pwd, path_env);
			if (!path_env)
				exit(STATUS_GENERAL_ERR);
			ft_free(&tmp);
			i += ft_strlen(pwd);
		}
		else if (path_env[i] == ':' && path_env[i + 1] == ':')
		{
			tmp = path_env;
			front = ft_substr(path_env, 0, i + 1);
			back = ft_strdup(path_env + i + 1);
			ft_free(&tmp);
			tmp = ft_strjoin(front, pwd);
			path_env = ft_strjoin(tmp, back);
			if (!front || !back || !tmp || !path_env)
				exit(1);
			ft_free(&front);
			ft_free(&back);
			ft_free(&tmp);
			i += ft_strlen(pwd);
		}
		else if (path_env[i] == ':' && !path_env[i + 1])
		{
			tmp = path_env;
			path_env = ft_strjoin(path_env, pwd);
			if (!path_env)
				exit(STATUS_GENERAL_ERR);
			ft_free(&tmp);
			i += ft_strlen(pwd);
		}
		else
			i++;
	}
	return (path_env);
}

void
	ft_do_command_err(char *c, char *err_arg, char *err_msg, int err_status)
{
	if (err_status == NO_ERROR)
	{
		ft_put_cmderror(c, COMMAND_NOT_FOUND_ERR_MSG);
		g_status = STATUS_COMMAND_NOT_FOUND;
	}
	else
	{
		ft_put_cmderror(err_arg, err_msg);
		g_status = err_status;
	}
}

void
	do_command(t_command *c, char **environ)
{
	char		**argv;
	char		**paths;
	char		*tmp;
	char		*command;
	char		*path_env;
	char		**head;
	struct stat	buf;
	char		*err_msg;
	char		*err_arg;
	int			err_status;

	if (!c || !environ)
		exit(STATUS_GENERAL_ERR);
	if (!c->args)
		exit(g_status);
	argv = ft_convert_list(c->args);
	if (!argv)
		exit(STATUS_GENERAL_ERR);
	command = ft_strdup(argv[0]);
	if (!command)
		exit(STATUS_GENERAL_ERR);
	err_msg = NULL;
	err_arg = NULL;
	err_status = NO_ERROR;
	path_env = ft_getenv("PATH");
	if (argv[0][0] == '/' || argv[0][0] == '.' || !path_env || !*path_env)
	{
		if (stat(argv[0], &buf) != 0)
		{
			ft_put_cmderror(argv[0], strerror(errno));
			g_status = STATUS_COMMAND_NOT_FOUND;
			exit(g_status);
		}
		else if (buf.st_mode & S_IFDIR)
		{
			ft_put_cmderror(argv[0], IS_DIR_ERROR_MSG);
			g_status = STATUS_CANNOT_EXECUTE;
			exit(g_status);
		}
		if (execve(argv[0], argv, environ) < 0)
		{
			ft_put_cmderror(argv[0], strerror(errno));
			g_status = STATUS_CANNOT_EXECUTE;
			exit(g_status);
		}
	}
	else
	{
		path_env = get_pathenv(path_env);
		paths = ft_split(path_env, ':');
		if (!path_env || !paths)
			exit(STATUS_GENERAL_ERR);
		head = paths;
		while (*paths)
		{
			ft_free(&(argv[0]));
			tmp = ft_strjoin(*paths, "/");
			if (tmp)
				argv[0] = ft_strjoin(tmp, command);
			if (!tmp || !argv[0])
				exit(STATUS_GENERAL_ERR);
			ft_free(&tmp);
			if (stat(argv[0], &buf) == 0)
			{
				if (buf.st_mode & S_IFDIR)
				{
					err_arg = ft_strdup(argv[0]);
					err_msg = ft_strdup(IS_DIR_ERROR_MSG);
					err_status = STATUS_COMMAND_NOT_FOUND;
				}
				if (execve(argv[0], argv, environ) < 0)
				{
					err_arg = ft_strdup(argv[0]);
					err_msg = ft_strdup(strerror(errno));
					err_status = STATUS_CANNOT_EXECUTE;
				}
			}
			paths++;
		}
		ft_do_command_err(command, err_arg, err_msg, err_status);
		ft_free(&err_msg);
		ft_free(&err_arg);
		ft_free(&command);
		ft_free(&path_env);
		ft_free_split(&head);
		ft_free_split(&argv);
		ft_free(&g_pwd);
		ft_lstclear(&g_env, free);
		exit(g_status); // still reachableのリークが残っているため要修正
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

int
	ft_execute_builtin(t_command *c)
{
	char	**argv;
	int		res;
	int		std_fds[3];

	res = KEEP_RUNNING;
	ft_save_fds(std_fds);
	if (ft_set_redirection(c->redirects) == FALSE)
		return (STOP);
	if (c->args)
	{
		argv = ft_convert_list(c->args);
		if (!argv)
		{
			g_status = 1;
			return (STOP);
		}
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
		else if (!ft_strcmp(argv[0], "exit"))
			res = ft_exit(argv);
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

static pid_t
	start_command(t_command *c, t_bool ispipe, t_bool haspipe, int lastpipe[2], char **environ)
{
	pid_t	pid;
	int		newpipe[2];

	if (ispipe)
		pipe(newpipe);
	pid = fork();
	if (pid == 0)
	{
		if (haspipe)
		{
			close(lastpipe[1]);
			dup2(lastpipe[0], STDIN_FILENO);
			close(lastpipe[0]);
		}
		if (ispipe)
		{
			close(newpipe[0]);
			dup2(newpipe[1], STDOUT_FILENO);
			close(newpipe[1]);
		}
		if (is_builtin(c))
		{
			ft_execute_builtin(c);
			exit(g_status); // still reachableのリークが残っているため要修正
		}
		else if (ft_set_redirection(c->redirects))
			do_command(c, environ);
	}
	if (haspipe)
	{
		close(lastpipe[0]);
		close(lastpipe[1]);
	}
	if (ispipe)
	{
		lastpipe[0] = newpipe[0];
		lastpipe[1] = newpipe[1];
	}
	return (pid);
}

t_command
	*ft_execute_pipeline(t_command *c, char **environ)
{
	t_bool	haspipe;
	int		lastpipe[2];
	int		res;

	haspipe = FALSE;
	ft_memset(lastpipe, -1, sizeof(int) * 2);
	while (c)
	{
		res = ft_expand_env_var(c);
		if (res == COMPLETED)
		{
			if (c->args || c->redirects)
			{
				c->pid = start_command(c, is_pipe(c), haspipe, lastpipe, environ);
				haspipe = is_pipe(c);
				if (haspipe)
					c = c->next;
				else
					break ;
			}
			else
			{
				c = c->next;
				break;
			}
		}
		else if (res == REDIRECT_DELETED)
		{
			c = c->next;
			break;
		}
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
	int			term_status;

	if (ft_init_env() == STOP)
		return (EXIT_FAILURE);
	if (ft_init_pwd() == STOP)
	{
		ft_lstclear(&g_env, free);
		return (EXIT_FAILURE);
	}
	while (1)
	{
		ft_putstr_fd(PROMPT, STDERR_FILENO);
		ft_sig_prior();
		res = get_next_line(STDIN_FILENO, &line);
		if (res == 0 && ft_strlen(line) == 0)
		{
			ft_putstr_fd(EXIT_PROMPT, STDERR_FILENO);
			exit(0);
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
				return (1);
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
						if (!commands || waitpid(commands->pid, &term_status, 0) < 0)
							exit_with_error();
						if (WIFEXITED(term_status))
							g_status = WEXITSTATUS(term_status);
						else if (!commands)
							break ;
					}
				}
				commands = commands->next;
			}
			if (res == EXIT)
			{
				ft_putstr_fd(EXIT_PROMPT, STDERR_FILENO);
				break;
			}
		}
		ft_free(&line);
		ft_free(&trimmed);
		get_next_line(STDIN_FILENO, NULL);
		ft_clear_commands(&head);
	}
	ft_free(&line);
	ft_free(&trimmed);
	get_next_line(STDIN_FILENO, NULL);
	ft_clear_commands(&head);
	ft_free(&g_pwd);
	ft_lstclear(&g_env, free);
	exit(g_status);
}
