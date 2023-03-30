#include "../../includes/minishell.h"

int	ft_pwd(void)
{
	char	buffer[4096];
	char	*cwd;

	cwd = getcwd(buffer, sizeof(buffer));
	if (cwd == NULL)
	{
		perror("getcwd");
		return (1);
	}
	ft_printf("%s\n", cwd);
	//free(cwd);
	ft_bzero(buffer, 4096);
	return (0);
}
