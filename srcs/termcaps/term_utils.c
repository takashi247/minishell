#include "minishell_sikeda.h"

int ft_putchar(int c)
{
	return (write(1, &c, 1));
}
