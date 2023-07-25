/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anitasulistiyawati <anitasulistiyawati@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:11:04 by anitasulist       #+#    #+#             */
/*   Updated: 2022/11/18 12:25:30 by anitasulist      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    ft_lstdelone(t_list *lst, void (*del)(void*))
{
    if (lst == NULL || del == NULL)
        return ;
    (*del)(lst->content);
    free(lst);
}
// fungsi ini buat menghapus node bserta isiannya
/*
// the func that delete the content
// replaced by 'd' to proof that it is deleted
void delete(void *content) {
    // free(content);
    (*(char *)content) = 'd';
}

int main()
{
    // create a content to be freed
    char *a = malloc(1);
    *a ='a';

    // create a node to delete
    t_list *list = ft_lstnew(a);

    // call the func to delete node
    ft_lstdelone(list, &delete);

    printf("after delete: %c", *a);
}
*/