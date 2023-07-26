#include "libft.h"
#include <stdio.h>

char **ft_list_to_array(t_list *list)
{
    t_list *tmp;
    char **array;
    int i;

    tmp = list;
    i = 0;
    array = malloc(sizeof(char *) * (ft_lstsize(list) + 1));
    if (array == NULL)
        return (NULL);
    while (tmp != NULL)
    {
        array[i] = ft_strdup((char *)(tmp->content));
        if (array[i] == NULL) {
            i--;
            while (i >= 0) {
                free(array[i]);
                i--;
            }
            free(array);
            return (NULL);
        }
        tmp = tmp->next;
        i++;
    }
    array[i] = NULL;
    return (array);
}