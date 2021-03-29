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
	do_command(char *line, char **environ)
{
	char	**argv;

	argv = ft_split(line, ' ');
	argv[0] = ft_strjoin("/bin/", argv[0]);
	execve(argv[0], argv, environ);
	exit_with_error("execve");
}

int
	main(void)
{
	char		*line;
	pid_t		pid;
	int			status;
	extern char	**environ;

	ft_putstr_fd(PROMPT, STDOUT_FILENO);
	while (get_next_line(STDIN_FILENO, &line) == 1 &&
		ft_strncmp(line, "exit", 5))
	{
		if ((pid = fork()) < 0)
			exit_with_error("fork");
		else if (pid == 0)
			do_command(line, environ);
		if ((pid = waitpid(pid, &status, 0)) < 0)
			exit_with_error("wait");
		FREE(line);
		ft_putstr_fd(PROMPT, STDOUT_FILENO);
	}
	FREE(line);
	ft_putstr_fd(EXIT_PROMPT, STDOUT_FILENO);
	exit(0);
}
