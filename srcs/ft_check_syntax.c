#include "../includes/minishell.h"

static void	ft_increment(t_parsing *parse, char c)
{
	parse->i++;
	while (parse->input[parse->i] != c)
		parse->i++;
	parse->i++;
}

static int	ft_len(t_parsing *parse)
{
	int		j;

	parse->i = 0;
	j = 0;
	while (parse->input[parse->i])
	{
		if (parse->input[parse->i] == '\"')
			ft_increment(parse, '\"');
		else if (parse->input[parse->i] == '\'')
			ft_increment(parse, '\'');
		else
		{
			j++;
			parse->i++;
		}
	}
	return (j);
}

static char	*ft_fill(t_parsing *parse, char *s)
{
	int	j;

	parse->i = 0;
	j = 0;
	while (parse->input[parse->i])
	{
		if (parse->input[parse->i] == '\"')
			ft_increment(parse, '\"');
		else if (parse->input[parse->i] == '\'')
			ft_increment(parse, '\'');
		else
		{
			s[j] = parse->input[parse->i];
			j++;
			parse->i++;
		}
	}
	s[j] = '\0';
	return (s);
}

int	ft_check_syntax(t_parsing *parse)
{
	char	*s;

	s = malloc(sizeof(char) * (ft_len(parse) + 1));
	s = ft_fill(parse, s);
	if (ft_strnstr(s, "<<<", ft_strlen(s))
		|| ft_strnstr(s, ">>>", ft_strlen(s))
		|| ft_strnstr(s, "> >", ft_strlen(s))
		|| ft_strnstr(s, "< <", ft_strlen(s))
		|| ft_strnstr(s, "\\", ft_strlen(s))
		|| ft_strnstr(s, ";", ft_strlen(s))
		|| ft_strnstr(s, "||", ft_strlen(s)))
	{
		ft_error("syntax error\n");
		free(s);
		return (0);
	}
	free(s);
	parse->i = 0;
	return (1);
}
