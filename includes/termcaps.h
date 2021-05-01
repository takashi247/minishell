#ifndef TERMCAPS_H
# define TERMCAPS_H

# include <term.h>
# include <termios.h>

# define C_EOF 4
# define C_DEL 127
# define K_UP "\e[A"
# define K_DOWN "\e[B"
# define K_RIGHT "\e[C"
# define K_LEFT "\e[D"

# define K_HOME "\e[H"
# define K_END "\e[F"

/* init_term.c */
int	ft_init_term(void);

#endif
