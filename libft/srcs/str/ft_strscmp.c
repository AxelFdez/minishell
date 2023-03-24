/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strscmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chmassa <chrisdev427@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 09:03:01 by chmassa           #+#    #+#             */
/*   Updated: 2023/03/23 12:58:02 by chmassa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strscmp(char **strtab, char *s)
{
	int	i;

	i = 0;
	while (strtab[i])
	{
		if (ft_strcmp(s, strtab[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}
