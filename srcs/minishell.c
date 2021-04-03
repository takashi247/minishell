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
			exit_with_error("malloc");
		FREE(tmp);
		if (execve(argv[0], argv, environ) < 0)
			exit_with_error("execve");
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

int
	main(void)
{
	char		*line;
	pid_t		pid;
	int			status;
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
		ft_strncmp(line, "exit", 5))
	{
		if ((ft_make_token(&tokens, line) != COMPLETED) || !(commands = ft_make_command(tokens)))
		{
			FREE(line);
			ft_lstclear(&tokens, free);
			return (1);
		}
		head = commands;
		while (commands)
		{
			if (!ft_strncmp(commands->op, ";", 1))
			{
				if ((pid = fork()) < 0)
					exit_with_error("fork");
				else if (pid == 0)
					do_command(commands, environ);
				if ((pid = waitpid(pid, &status, 0)) < 0)
					exit_with_error("wait");
				commands = commands->next;
			}
			else if (!ft_strncmp(commands->op, "|", 1))
			{
				do_simple_pipe(commands, environ);
				commands = commands->next->next;
			}
		}
		FREE(line);
		get_next_line(STDIN_FILENO, NULL);
		ft_clear_commands(&head);
		ft_putstr_fd(PROMPT, STDOUT_FILENO);
	}
	FREE(line);
	get_next_line(STDIN_FILENO, NULL);
	FREE(g_pwd);
	ft_putstr_fd(EXIT_PROMPT, STDOUT_FILENO);
	exit(0);
}
