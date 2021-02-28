#include "minishell_tnishina.h"
#include "libft.h"

// need to use g_* prefix to pass norm
extern char **environ;

int
	exit_with_error(char *str)
{
	printf("%s: %s\n", str, strerror(errno));
	exit(1);
}

void
	do_command(char *line)
{
	char	*argv[2];

	argv[0] = ft_strjoin("/bin/", line);
	argv[1] = NULL;
	execve(argv[0], argv, environ);
	exit_with_error("execve");
}

int
	main(void)
{
	char	*line;
	pid_t	pid;
	int		status;

	write(STDOUT_FILENO, PROMPT, ft_strlen(PROMPT));
	while (get_next_line(STDIN_FILENO, &line) == 1 &&
		ft_strncmp(line, "exit", 5))
	{
		if ((pid = fork()) < 0)
			exit_with_error("fork");
		else if (pid == 0)
			do_command(line);
		if ((pid = waitpid(pid, &status, 0)) < 0)
			exit_with_error("wait");
		ft_free_str(&line);
		write(STDOUT_FILENO, PROMPT, ft_strlen(PROMPT));
	}
	write(STDOUT_FILENO, EXIT_PROMPT, ft_strlen(EXIT_PROMPT));
	exit(0);
}
