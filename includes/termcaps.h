#ifndef TERMCAPS_H
# define TERMCAPS_H

# include <term.h>
# include <termios.h>
# include <sys/ioctl.h>

# define C_EOF 4
# define C_ESC 27
# define C_DEL 127
# define K_UP "\e[A"
# define K_DOWN "\e[B"
# define K_RIGHT "\e[C"
# define K_LEFT "\e[D"

# define K_HOME "\e[H"
# define K_END "\e[F"

typedef struct s_termdef
{
	char	*cm;
	char	*ce;
	char	*cr;
}	t_termdef;

typedef struct s_cursor
{
	int	row;
	int	col;
}	t_cursor;

typedef struct s_terminfo
{
	int			maxcol;
	int			maxrow;
	t_cursor	start;
	t_cursor	prev;
	t_cursor	current;
	t_termdef	def;
}	t_terminfo;

/* init_term.c */
int	ft_init_term(void);

/* edit_term.c */
int	ft_backspace(const char *pre_line, size_t len);

/* term_utils.c */
int ft_putchar(int c);
int	ft_get_cursor_position(int *row, int *col);
int	ft_update_current_position(void);
int	ft_get_win_size(void);

#endif
