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



static int	ft_check_after_token(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((s[i] == '|' || s[i] == '>' || s[i] == '<') && (s[i +1] == '\0'))
		{
			ft_printf("minishell: syntax error near unexpected token `newline'\n");
			return (0);
		}

		i++;
	}
	return (1);
}
int	ft_check_syntax(t_parsing *parse)
{
	int		i;
	char	*s;
	char	*lex[10];
	lex[0] = "<<<";
	lex[1] = ">>>";
	lex[2] = "< <";
	lex[3] = "> >";
	lex[4] = "<>";
	lex[5] = "><";
	lex[6] = "\\";
	lex[7] = ";";
	lex[8] = "||";
	lex[9] = NULL;

	s = malloc(sizeof(char) * (ft_len(parse) + 1));
	s = ft_fill(parse, s);
	i = 0;
	while (lex[i])
	{
		if (ft_strnstr(s, lex[i], ft_strlen(s)))
		{
			ft_printf("minishell: syntax error near unexpected token `%s'\n", lex[i]);
			free(s);
			parse->ret_value = 258;
			return (258);
		}
		i++;
	}
	if (ft_check_after_token(s) == 0)
	{
		free(s);
		parse->ret_value = 258;
		return (258);
	}
	free(s);
	parse->i = 0;
	parse->ret_value = 0;
	return (0);
}
