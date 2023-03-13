/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chmassa <chrisdev427@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 11:44:44 by chmassa           #+#    #+#             */
/*   Updated: 2023/03/13 15:01:27 by chmassa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LST_H
# define LST_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

//**** struct lst **************************************************************
typedef struct s_list
{
	char			*str;
	struct s_list	*prev;
	struct s_list	*next;
}				t_list;

//**** lst new node ************************************************************
t_list	*ft_lstnew(char *str);
//**** lst new tools ***********************************************************
t_list	*ft_lstcpy(t_list **lst);
t_list	*ft_lstlast(t_list *lst);
int		ft_lstsize(t_list *lst);
//***** lstadd *****************************************************************
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_position(t_list **lst, t_list *new, int position);
void	ft_lstadd_back(t_list **lst, t_list *new);
//***** lstdel *****************************************************************
void	ft_lstdel_front(t_list **lst);
void	ft_lstdel_back(t_list **lst);
void	ft_lstdel_position(t_list **lst, int position);
void	ft_lstdel_all(t_list **lst);
//***** lstprint ******************************************************
void	lstprint(t_list *lst);
void	ft_lstprint_from_head(t_list *lst);
void	ft_lstprint_from_tail(t_list *lst);

#endif
