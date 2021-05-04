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

/*
cm:
String of commands to position the cursor at line l, column c.
Both parameters are origin-zero, and are defined relative to the screen,
not relative to display memory. All display terminals except a few very
obsolete ones support `cm', so it is acceptable for an application
program to refuse to operate on terminals lacking `cm'.

cd:
String of commands to clear the line the cursor is on, and all the lines
below it, down to the bottom of the screen. This command string should be
used only with the cursor in column zero; their effect is undefined
if the cursor is elsewhere.

cr:
String of commands to move the cursor to the beginning of the line it is on.
If this capability is not specified, many programs assume they can use
the ASCII carriage return character for this.

sf:
String of commands to scroll the screen one line up, assuming it is output
with the cursor at the beginning of the bottom line.
*/
typedef struct s_termdef
{
	char	*cm;
	char	*cd;
	char	*cr;
	char	*sf;
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
int	ft_backspace(const char *pre_line, size_t *len);
int	ft_input_char(const char *buf, char *pre_line,
		size_t *len, size_t *allocated);

/* get_line.c */
int	ft_get_line(char **line);

/* handle_keys.c */
int	ft_handle_keys_loop(char *pre_line, size_t *len);

/* term_utils.c */
int	ft_putchar(int c);
int	ft_get_cursor_position(int *row, int *col);
int	ft_update_current_position(void);
int	ft_get_win_size(void);

#endif
