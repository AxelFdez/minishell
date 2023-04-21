/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_meta_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axfernan <axfernan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:31:46 by axfernan          #+#    #+#             */
/*   Updated: 2023/04/20 11:31:47 by axfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_meta_char(int c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}
