#include "minishell_tnishina.h"
#include "minishell_sikeda.h"
#include "libft.h"

int
	exit_with_error(char *str)
{
	printf("%s: %s\n", str, strerror(errno));
	exit(1);
}

void
	do_command(t_command *c, char **environ)
{
	char	**argv;
	char	**head;
	char	*tmp;

	if (!c || !environ)
		exit(1);
	if (!(argv = (char**)malloc(sizeof(char*) * (ft_lstsize(c->args) + 1))))
		exit(1);
	head = argv;
	while (c->args)
	{
		*argv = c->args->content;
		argv++;
		c->args = c->args->next;
	}
	*argv = NULL;
	argv = head;
	tmp = argv[0];
	if (!(argv[0] = ft_strjoin("/bin/", argv[0])))
		exit_with_error("malloc");
	FREE(tmp);
	if (execve(argv[0], argv, environ) < 0)
	{
		tmp = argv[0];
		if (!(argv[0] = ft_strjoin("/usr", argv[0])))
			exit_with_error("malloc"); //おそらくこのケースもリークが出てしまっているので要修正
		FREE(tmp);
		if (execve(argv[0], argv, environ) < 0)
			exit_with_error("execve"); //このケースもリークが出てしまっているので要修正
	}
}

static void
	close_n_wait(int pipefd[2], pid_t childs[2], int *status, int *res)
{
	close(pipefd[0]);
	close(pipefd[1]);
	*res = waitpid(childs[0], status, 0);
	*res = waitpid(childs[1], status, 0);
}

static void
	do_simple_pipe(t_command *commands, char **environ)
{
	int		pipefd[2];
	int		res;
	int		status;
	pid_t	childs[2];

	res = pipe(pipefd);
	if ((childs[0] = fork()) < 0)
		exit_with_error("fork");
	else if (childs[0] == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		do_command(commands, environ);
	}
	if ((childs[1] = fork()) < 0)
		exit_with_error("fork");
	else if (childs[1] == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		close(pipefd[0]);
		do_command(commands->next, environ);
	}
	close_n_wait(pipefd, childs, &status, &res);
}

static t_bool
	is_redirect(char *str)
{
	if (!ft_strncmp(str, REDIRECT_IN, ft_strlen(REDIRECT_IN))
	|| !ft_strncmp(str, REDIRECT_OUT, ft_strlen(REDIRECT_OUT))
	|| !ft_strncmp(str, APPEND_REDIRECT_OUT, ft_strlen(APPEND_REDIRECT_OUT)))
		return (TRUE);
	else
		return (FALSE);
}

t_bool
	ft_set_redirection(t_list **args)
{
	t_list	*head;
	t_list	*prev;
	int		fd_from;
	int		fd_to;
	char	*path;
	char	*redirect_op;

	prev = NULL;
	head = *args;
	fd_from = -1;
	redirect_op = NULL;
	path = NULL;
	while (*args)
	{
		if (ft_isdigit(((char*)((*args)->content))[0]) && ft_isnumeric((char*)((*args)->content)) && is_redirect((char*)((*args)->next->content)))
		{
			fd_from = ft_atoi((char*)((*args)->content));
			if (fd_from < 0 || FD_MAX < fd_from)
			{
				ft_put_fderror(fd_from);
				g_status = 1;
				return (FALSE);
			}
			redirect_op = ft_strdup((char*)((*args)->next->content));
			path = ft_strdup((char*)((*args)->next->next->content));
			if (!redirect_op || !path)
			{
				FREE(redirect_op);
				FREE(path);
				g_status = 1;
				return (FALSE);
			}
			if (prev)
				prev->next = (*args)->next->next->next;
			else
				head = (*args)->next->next->next;
			ft_lstdelone((*args)->next->next, free);
			ft_lstdelone((*args)->next, free);
			ft_lstdelone((*args), free);
			if (prev)
				*args = prev->next;
			else
				*args = head;
		}
		else if (is_redirect((char*)((*args)->content)))
		{
			redirect_op = ft_strdup((char*)((*args)->content));
			path = ft_strdup((char*)((*args)->next->content));
			if (!redirect_op || !path)
			{
				FREE(redirect_op);
				FREE(path);
				g_status = 1;
				return (FALSE);
			}
			if (prev)
				prev->next = (*args)->next->next;
			else
				head = (*args)->next->next;
			ft_lstdelone((*args)->next, free);
			ft_lstdelone((*args), free);
			if (prev)
				*args = prev->next;
			else
				*args = head;
		}
		if (!redirect_op)
		{
			prev = *args;
			*args = (*args)->next;
		}
		else if (!(ft_strcmp(redirect_op, APPEND_REDIRECT_OUT)))
		{
			fd_to = open(path, O_WRONLY | O_CREAT | O_APPEND, 0666);
			if (fd_to < 0)
			{
				ft_put_cmderror(path, strerror(errno));
				g_status = 1;
				FREE(redirect_op);
				FREE(path);
				return (FALSE);
			}
			if (fd_from == -1)
				fd_from = STDOUT_FILENO;
			dup2(fd_to, fd_from);
			close(fd_to);
		}
		else if (!(ft_strcmp(redirect_op, REDIRECT_OUT)))
		{
			fd_to = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			if (fd_to < 0)
			{
				ft_put_cmderror(path, strerror(errno));
				g_status = 1;
				FREE(redirect_op);
				FREE(path);
				return (FALSE);
			}
			if (fd_from == -1)
				fd_from = STDOUT_FILENO;
			dup2(fd_to, fd_from);
			close(fd_to);
		}
		else if (!(ft_strcmp(redirect_op, REDIRECT_IN)))
		{
			fd_to = open(path, O_RDONLY);
			if (fd_to < 0)
			{
				ft_put_cmderror(path, strerror(errno));
				g_status = 1;
				FREE(redirect_op);
				FREE(path);
				return (FALSE);
			}
			if (fd_from == -1)
				fd_from = STDIN_FILENO;
			dup2(fd_to, fd_from);
			close(fd_to);
		}
		FREE(redirect_op);
		FREE(path);
	}
	*args = head;
	return (TRUE);
}

int
	main(void)
{
	char		*line;
	char		*trimmed;
	pid_t		pid;
	extern char	**environ;
	t_list		*tokens;
	t_command	*head;
	t_command	*commands;

	if (ft_init_env() == STOP)
		return (EXIT_FAILURE);
	if (ft_init_pwd() == STOP)
	{
		ft_lstclear(&g_env, free);
		return (EXIT_FAILURE);
	}
	ft_putstr_fd(PROMPT, STDOUT_FILENO);
	while (get_next_line(STDIN_FILENO, &line) == 1 &&
		(trimmed = ft_strtrim(line, " \t")) &&
		ft_strcmp(trimmed, "exit"))
	{
		if ((ft_make_token(&tokens, trimmed, ft_is_delimiter_or_quote) != COMPLETED)
		|| ft_make_command(&commands, tokens) != COMPLETED
		|| ft_expand_env_var(commands) != COMPLETED)
		{
			FREE(line);
			FREE(trimmed);
			ft_lstclear(&tokens, free);
			return (1);
		}
		head = commands;
		while (commands)
		{
			if (!ft_strcmp(commands->op, ";") || !ft_strcmp(commands->op, NEWLINE))
			{
				if ((pid = fork()) < 0)
					exit_with_error("fork");
				else if (pid == 0)
				{
					if (ft_set_redirection(&(commands->args)))
						do_command(commands, environ);
					//リダイレクトが失敗した場合にはそのままexitする形にしているのですが、exitする際にリークが出てしまっているので要修正
					exit(g_status);
				}
				if ((pid = waitpid(pid, &g_status, 0)) < 0)
					exit_with_error("wait");
				commands = commands->next;
			}
			else if (!ft_strcmp(commands->op, "|"))
			{
				do_simple_pipe(commands, environ);
				commands = commands->next->next;
			}
		}
		FREE(line);
		FREE(trimmed);
		get_next_line(STDIN_FILENO, NULL);
		ft_clear_commands(&head);
		ft_putstr_fd(PROMPT, STDOUT_FILENO);
	}
	FREE(line);
	FREE(trimmed);
	get_next_line(STDIN_FILENO, NULL);
	FREE(g_pwd);
	ft_lstclear(&g_env, free);
	ft_putstr_fd(EXIT_PROMPT, STDOUT_FILENO);
	exit(0);
}
