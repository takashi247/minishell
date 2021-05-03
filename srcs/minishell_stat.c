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
		exit(1);
	tmp = NULL;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (path_env);
	i = 0;
	while (path_env[i])
	{
		if (!i && path_env[i] == ':')
		{
			tmp = path_env;
			path_env = ft_strjoin(pwd, path_env);
			if (!path_env)
				exit(1);
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
				exit(1);
			ft_free(&tmp);
			i += ft_strlen(pwd);
		}
		else
			i++;
	}
	ft_free(&pwd);
	return (path_env);
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

	if (!c || !environ)
		exit(1);
	argv = ft_convert_list(c->args);
	if (!argv)
		exit(1);
	command = ft_strdup(argv[0]);
	if (!command)
		exit(1);
	if (stat(argv[0], &buf) == 0)
	{
		if (execve(argv[0], argv, environ) < 0)
			exit(1);
	}
	else
	{
		if (ft_getenv("PATH"))
		{
			path_env = get_pathenv(ft_getenv("PATH"));
			if (!path_env)
				exit(1);
		}
		else
			path_env = NULL;
		paths = ft_split(path_env, ':');
		head = paths;
		while (*paths)
		{
			ft_free(&(argv[0]));
			tmp = ft_strjoin(*paths, "/");
			if (tmp)
				argv[0] = ft_strjoin(tmp, command);
			if (!tmp || !argv[0])
				exit(1);
			ft_free(&tmp);
			if (stat(argv[0], &buf) == 0)
			{
				if (execve(argv[0], argv, environ) < 0)
					exit(1);
			}
			else
				paths++;
		}
		ft_put_cmderror(command, "command not found");
		ft_free(&command);
		ft_free(&path_env);
		ft_free_split(&head);
		ft_free_split(&argv);
		ft_free(&g_pwd);
		ft_lstclear(&g_env, free);
		exit(1); // still reachableのリークが残っているため要修正
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

	res = STOP;
	ft_save_fds(std_fds);
	if (ft_set_redirection(&(c->args)) == FALSE)
		return (res);
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
	ft_restore_fds(std_fds);
	return (res);
}

static t_bool
	is_builtin(t_command *c)
{
	if (!ft_strcmp((char* )(c->args->content), "echo")
		|| !ft_strcmp((char* )(c->args->content), "cd")
		|| !ft_strcmp((char* )(c->args->content), "pwd")
		|| !ft_strcmp((char* )(c->args->content), "export")
		|| !ft_strcmp((char* )(c->args->content), "unset")
		|| !ft_strcmp((char* )(c->args->content), "env")
		|| !ft_strcmp((char* )(c->args->content), "exit"))
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
			exit(0); // still reachableのリークが残っているため要修正
		}
		else if (ft_set_redirection(&(c->args)))
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

	haspipe = FALSE;
	ft_memset(lastpipe, -1, sizeof(int) * 2);
	while (c)
	{
		c->pid = start_command(c, is_pipe(c), haspipe, lastpipe, environ);
		haspipe = is_pipe(c);
		if (haspipe)
			c = c->next;
		else
			break ;
	}
	return (c);
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

	if (ft_init_env() == STOP)
		return (EXIT_FAILURE);
	if (ft_init_pwd() == STOP)
	{
		ft_lstclear(&g_env, free);
		return (EXIT_FAILURE);
	}
	ft_putstr_fd(PROMPT, STDERR_FILENO);
	while (get_next_line(STDIN_FILENO, &line) == 1
		&& (trimmed = ft_strtrim(line, " \t")))
	{
		if (ft_make_token(&tokens, trimmed, ft_is_delimiter_or_quote) != COMPLETED
		|| ft_make_command(&commands, tokens) != COMPLETED
		|| ft_expand_env_var(commands) != COMPLETED)
		{
			ft_free(&line);
			ft_free(&trimmed);
			ft_lstclear(&tokens, free);
			get_next_line(STDIN_FILENO, NULL);
			return (1);
		}
		ft_free(&line);
		ft_free(&trimmed);
		get_next_line(STDIN_FILENO, NULL);
		res = KEEP_RUNNING;
		head = commands;
		while (commands)
		{
			if (is_builtin(commands) && !is_pipe(commands))
			{
				res = ft_execute_builtin(commands);
				if (res != KEEP_RUNNING)
					break;
				commands = commands->next;
				continue ;
			}
			commands = ft_execute_pipeline(commands, environ);
			if (waitpid(commands->pid, &g_status, 0) < 0)
				exit_with_error();
			commands = commands->next;
		}
		if (res != KEEP_RUNNING)
			break;
		ft_clear_commands(&head);
		ft_putstr_fd(PROMPT, STDERR_FILENO);
	}
	ft_free(&line);
	ft_free(&trimmed);
	get_next_line(STDIN_FILENO, NULL);
	ft_clear_commands(&head);
	ft_free(&g_pwd);
	ft_lstclear(&g_env, free);
	exit(g_status);
}