#include "libft.h"

void	ft_lst_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(void *, void *), void (*del)(void *))
{
	t_list *current;
	t_list *previous;
	t_list *tmp;

	if ((begin_list == NULL) || (*begin_list == NULL))
		return;

	previous = NULL;
	current = *begin_list;
	while (current != NULL)
	{
		if (cmp(current->content, data_ref) == 0)
		{
			tmp = current->next;
			del(current->content);
			free(current);
			if (previous == NULL)
				*begin_list = tmp;
			else
				previous->next = tmp;
			current = tmp;
		}
		else {
			previous = current;
			current = current->next;
		}
	}
}