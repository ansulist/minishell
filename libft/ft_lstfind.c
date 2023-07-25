#include "libft.h"

t_list *ft_lstfind(t_list *list, int(cmp)(void *, void *), void *data_ref)
{
    while (list != NULL)
    {
        if (cmp(list->content, data_ref) == 0)
            return (list);
        list = list->next;
    }
    return (NULL);
}