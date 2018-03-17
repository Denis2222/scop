typedef struct		s_list
{
	void 			*addr;
	unsigned int	value;
	size_t			size;
	struct s_list	*next;
}					t_list;

t_list 	*list_new(void *addr, size_t size);
t_list *list_new_uint(unsigned int u, size_t size);
int 	list_length(t_list *list);
void 	list_push(t_list **lst, t_list *to_add);
void 	list_push_back(t_list *l, t_list *to_add);

void 	*list_get(t_list *l, size_t n);

void	list_del(t_list **l);
void	list_del_one(t_list **l);
