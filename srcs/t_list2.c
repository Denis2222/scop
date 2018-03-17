/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_list2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 13:29:13 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/17 13:30:00 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void	list_push(t_list **lst, t_list *to_add)
{
	if (*lst)
		return (list_push_back(*lst, to_add));
	*lst = to_add;
}

void	list_push_back(t_list *l, t_list *to_add)
{
	if (l->next)
		return (list_push_back(l->next, to_add));
	l->next = to_add;
}

void	list_del(t_list **l)
{
	if (*l)
	{
		list_del(&((*l)->next));
		list_del_one(l);
	}
}

void	list_del_one(t_list **l)
{
	free(*l);
	*l = NULL;
}
