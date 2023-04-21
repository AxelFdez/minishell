/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axfernan <axfernan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:44:34 by chmassa           #+#    #+#             */
/*   Updated: 2023/04/20 11:57:28 by axfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_free(const char *s1)
{
	char	*str;
	int		i;
	int		s1len;

	i = 0;
	s1len = 0;
	while (s1[s1len])
		s1len++;
	str = malloc(sizeof(char) * s1len + 1);
	if (str == NULL)
		return (NULL);
	else
	{
		while (s1[i])
		{
			str[i] = s1[i];
			i++;
		}
		str[i] = '\0';
	}
	free((char *)s1);
	return (str);
}
