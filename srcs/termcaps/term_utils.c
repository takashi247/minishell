#include "minishell_sikeda.h"

int
	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

/* get cursor position from syntax like "^[[31;12R" */
int
	ft_get_cursor_position(int *row, int *col)
{
	char			buf[32];
	unsigned int	i;
	int				ret;

	i = 0;
	ret = write(STDOUT_FILENO, "\x1b[6n", 4);
	if (ret != 4)
		return (UTIL_ERROR);
	while (i < sizeof(buf) - 1)
	{
		ret = read(STDIN_FILENO, buf + i, 1);
		if (ret != 1)
			break ;
		if (buf[i] == 'R')
			break ;
		i++;
	}
	buf[i] = '\0';
	if (buf[0] != C_ESC || buf[1] != '[')
		return (UTIL_ERROR);
	*row = ft_atoi(buf + 2) - 1;
	*col = ft_atoi(ft_strchr(buf + 2, ';') + 1) - 1;
	return (UTIL_SUCCESS);
}

int
	ft_update_current_position(void)
{
	g_ms.terminfo.prev.col = g_ms.terminfo.current.col;
	g_ms.terminfo.prev.row = g_ms.terminfo.current.row;
	ft_get_cursor_position(
		&g_ms.terminfo.current.row, &g_ms.terminfo.current.col);
	return (UTIL_SUCCESS);
}

int
	ft_get_win_size(void)
{
	struct winsize	ws;

	ioctl(1, TIOCGWINSZ, &ws);
	g_ms.terminfo.maxcol = ws.ws_col;
	g_ms.terminfo.maxrow = ws.ws_row;
	return (UTIL_SUCCESS);
}
