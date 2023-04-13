#include "../../includes/minishell.h"

int	ft_pwd(void)
{
	if (ft_get_current_position())
	{
		ft_printf("%s\n", ft_get_current_position());
		return (0);
	}
	return (1);
}
