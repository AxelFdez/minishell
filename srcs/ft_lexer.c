#include "../includes/minishell.h"

static int	ft_check_after_token(char *s)
{
	int		i;
	char	*ret;

	i = 0;
	ret = "minishell: syntax error near unexpected token `newline'\n";
	while (s[i])
	{
		if ((s[i] == '|' || s[i] == '>' || s[i] == '<') && (s[i +1] == '\0'))
		{
			ft_putstr(ret);
			return (0);
		}

		i++;
	}
	return (1);
}

static int	ft_check_syntax(t_parsing *parse, char *s)
{
	int		i;
	char	*err_message;

	i = 0;
	err_message = "minishell: syntax error near unexpected token";
	while (parse->lex[i])
	{
		if (ft_strnstr(s, parse->lex[i], ft_strlen(s)))
		{
			ft_printf("%s `%s'\n", err_message, parse->lex[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_unsupported_token(t_parsing *parse)
{
	char	*s;
	char	*err_message;
	int		i;

	i = 0;
	err_message = "minishell: error: `[\\] [;] [||]' unsupported token\n";
	s = malloc(sizeof(char) * (ft_len_str_to_cmp(parse) + 1));
	s = ft_fill_str_to_cmp(parse, s);
	if (ft_strchr(s, '\\') || ft_strchr(s, ';')
		|| (ft_strnstr(s, "||", ft_strlen(s))))
	{
		ft_putstr_fd(err_message, 2);
		free(s);
		parse->ret_value = 258;
		return (0);
	}
	free(s);
	parse->ret_value = 0;
	return (1);
}

int	ft_lexer(t_parsing *parse)
{
	char	*s;

	s = malloc(sizeof(char) * (ft_len_str_to_cmp(parse) + 1));
	s = ft_fill_str_to_cmp(parse, s);
	ft_init_lexer(parse);
	if (ft_check_after_token(s) == 0 || ft_check_syntax(parse, s) == 0)
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
