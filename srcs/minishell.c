#include "minishell_tnishina.h"
#include "minishell_sikeda.h"
#include "libft.h"

t_bool
	ft_is_end_with_escape(char *line)
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
		if (!(*trimmed))
			ft_exit_n_free_g_vars(STATUS_GENERAL_ERR);
		ft_strlcpy(*trimmed, tmp, size);
		ft_free(&tmp);
		final = (char *)malloc(sizeof(char) * 2);
		if (!final)
			ft_exit_n_free_g_vars(STATUS_GENERAL_ERR);
		len = ft_strlen(line);
		while (line[len] != '\\')
			final[0] = line[len--];
		final[1] = '\0';
		ft_strlcat(*trimmed, final, size);
		ft_free(&final);
	}
}

t_command
	*ft_convert_line(char **line, t_command **commands)
{
	char	*trim;
	t_list	*tokens;

	ft_add_space(line);
	trim = ft_strtrim(*line, " \t");
	if (trim && ft_is_end_with_escape(trim))
		add_final_char(&trim, *line);
	if (!trim
		|| ft_make_token(&tokens, trim, ft_is_delimiter_or_quote) != COMPLETED
		|| ft_make_command(commands, tokens) != COMPLETED)
	{
		ft_free(line);
		ft_free(&trim);
		ft_lstclear(&tokens, free);
		ft_exit_n_free_g_vars(STATUS_GENERAL_ERR);
	}
	ft_free(&trim);
	return (*commands);
}

static t_bool
	get_interactive_input(t_command **commands)
{
	char		*line;
	t_bool		res;

	ft_sig_prior();
	if (ft_get_line(&line) == GNL_ERROR)
		ft_exit_n_free_g_vars(STATUS_GENERAL_ERR);
	ft_sig_post();
	if (ft_is_end_with_escape(line))
	{
		ft_put_cmderror("\\", MULTILINE_ERROR_MSG);
		g_status = STATUS_GENERAL_ERR;
		res = FALSE;
	}
	else
	{
		ft_convert_line(&line, commands);
		res = TRUE;
	}
	ft_free(&line);
	return (res);
}

int
	main(int ac, char **av)
{
	t_command	*commands;
	int			res;

	if (!(ac == 1 || ac == 3))
		return (STATUS_GENERAL_ERR);
	if (init_minishell(ac) == UTIL_ERROR)
		return (EXIT_FAILURE);
	if (ac == 3)
		ft_run_commandline(av);
	while (1)
	{
		res = KEEP_RUNNING;
		if (get_interactive_input(&commands))
		{
			ft_run_commands(commands, &res);
			ft_clear_commands(&commands);
		}
		if (res == EXIT || res == EXIT_NON_NUMERIC)
			break ;
	}
	ft_exit_n_free_g_vars(g_status);
}
