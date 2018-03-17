/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_list.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 13:27:16 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/17 13:29:57 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

t_list	*list_new(void *addr, size_t size)
{
	t_list	*new;

	new = (t_list*)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->addr = addr;
	new->size = size;
	new->value = 0;
	new->next = NULL;
	return (new);
}

t_list	*list_new_uint(unsigned int u, size_t size)
{
	t_list	*new;

	new = (t_list*)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->value = u;
	new->addr = NULL;
	new->size = size;
	new->next = NULL;
	return (new);
}

int		list_length(t_list *list)
{
	int	len;

	len = 0;
	while (list)
	{
		len++;
		list = list->next;
	}
	return (len);
}

void	*list_get(t_list *l, size_t n)
{
	size_t	i;
	t_list	*list;

	list = l;
	i = 0;
	while (list)
	{
		if (i == n)
		{
			return (list->addr);
		}
		list = list->next;
		i++;
	}
	return (NULL);
}
