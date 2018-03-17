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

int 	list_length(t_list *list)
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
