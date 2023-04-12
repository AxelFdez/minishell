#include "../includes/minishell.h"

int	is_meta_char(int c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}
