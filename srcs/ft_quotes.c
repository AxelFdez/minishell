

#include "../includes/minishell.h"

void	ft_strdel_quotes(t_parsing *parse, char *str)
{
	parse->j = 0;
	while (str[parse->j])
	{
		if (str[parse->j] == '\'' || str[parse->j] == '\"')
		{
			parse->c = str[parse->j];
			parse->k = parse->j;
			while (str[parse->k])
			{
				str[parse->k] = str[parse->k +1];
				parse->k++;
			}
			while (str[parse->j] != parse->c)
				parse->j++;
			parse->k = parse->j;
			while (str[parse->k])
			{
				str[parse->k] = str[parse->k +1];
				parse->k++;
			}	
		}
		else
			parse->j++;
	}
	str[parse->j +1] = '\0';
}

static void	ft_prompt(t_parsing *parse, char c)
{
	char	*tmp;

	parse->prompt = ft_calloc(1, sizeof(char));
	parse->input = ft_strjoin_free_s1(parse->input, "\n");
	while (1)
	{
		tmp = readline("\033[1;31m>\033[0m ");
		parse->prompt = ft_strjoin_free_s1(parse->prompt, tmp);
		free(tmp);
		if (ft_found_char(tmp, c))
			break ;
		else
			parse->prompt = ft_strjoin_free_s1(parse->prompt, "\n");
	}
	parse->input = ft_strjoin_free_s1(parse->input, parse->prompt);
	free(parse->prompt);
	add_history(parse->input);
}

void	ft_quotes(t_parsing *parse)
{
	int	i;
	int	sgl_q;
	int	dbl_q;

	i = 0;
	sgl_q = 0;
	dbl_q = 0;
	while (parse->input[i])
	{
		if (parse->input[i] == '\"' && sgl_q == 0)
			dbl_q++;
		if (parse->input[i] == '\'' && dbl_q == 0)
			sgl_q++;
		i++;
	}
	if (dbl_q != 0 && dbl_q % 2 != 0)
		ft_prompt(parse, '\"');
	if (sgl_q != 0 && sgl_q % 2 != 0)
		ft_prompt(parse, '\'');
}
