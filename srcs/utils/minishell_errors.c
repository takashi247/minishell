#include "minishell_tnishina.h"

void
	ft_put_error(char *msg)
{
	int	fd;

	fd = STDERR_FILENO;
	ft_putstr_fd(PRG_NAME, fd);
	ft_putstr_fd(": ", fd);
	ft_putendl_fd(msg, fd);
}

void
	ft_put_syntaxerror_with_token(char *token)
{
	int	fd;

	fd = STDERR_FILENO;
	ft_putstr_fd(PRG_NAME, fd);
	ft_putstr_fd(": ", fd);
	ft_putstr_fd(SYNTAX_ERROR_MSG, fd);
	ft_putstr_fd(" `", fd);
	ft_putstr_fd(token, fd);
	ft_putendl_fd("\'", fd);
}
