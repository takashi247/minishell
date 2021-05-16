#include "minishell_tnishina.h"
#include "minishell_sikeda.h"
#include "libft.h"

void
	ft_save_fds(int std_fds[3])
{
	std_fds[0] = dup(STDIN_FILENO);
	std_fds[1] = dup(STDOUT_FILENO);
	std_fds[2] = dup(STDERR_FILENO);
	if (std_fds[0] < 0 || std_fds[1] < 0 || std_fds[2] < 0)
		ft_exit_n_free_g_vars(STATUS_GENERAL_ERR);
}

void
	ft_restore_fds(int std_fds[3])
{
	if (dup2(std_fds[0], STDIN_FILENO) < 0
		|| dup2(std_fds[1], STDOUT_FILENO) < 0
		|| dup2(std_fds[2], STDERR_FILENO) < 0)
		ft_exit_n_free_g_vars(STATUS_GENERAL_ERR);
	if (std_fds[0] != STDIN_FILENO)
		close(std_fds[0]);
	if (std_fds[1] != STDOUT_FILENO)
		close(std_fds[1]);
	if (std_fds[2] != STDERR_FILENO)
		close(std_fds[2]);
}
