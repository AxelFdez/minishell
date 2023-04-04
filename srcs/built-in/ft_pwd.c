#include "../../includes/minishell.h"

int	ft_pwd(t_parsing *parse)
{
	char	buffer[4096];
	char	*cwd;
	parse = NULL;
	cwd = getcwd(buffer, sizeof(buffer));
	if (cwd == NULL)
	{
		perror("getcwd");
		return (1);
	}
	ft_printf("%s\n", cwd);
	ft_bzero(buffer, 4096);
	return (0);
}
