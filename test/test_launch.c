#include "test_builtin.h"

#ifdef CDTEST
int
	test_launch(char **args)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;
	int		ret;

	pid = fork();
	if (pid < 0)
		ft_put_error("lsh");
	if (pid == 0)
	{
		ret = execvp(args[0], args);
		if (ret == -1)
			ft_put_error("lsh");
		exit(EXIT_FAILURE);
	}
	else
	{
		wpid = waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			wpid = waitpid(pid, &status, WUNTRACED);
	}
	return (1);
}

#else
int
	test_launch(char **args)
{
	(void)args;
	return (1);
}
#endif
