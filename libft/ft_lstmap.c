/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anitasulistiyawati <anitasulistiyawati@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 02:17:31 by anitasulist       #+#    #+#             */
/*   Updated: 2022/11/17 10:53:05 by anitasulist      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
/*
void ft_lstprint(t_list *lst, void (*print_content)(void *)) {
    int i;

    i = 0;
    while (lst != NULL) {
        printf("\n---------------------\n");
        printf("node %d: [", i);
        print_content(lst->content);
        printf("]\n");
        printf("---------------------\n");
        i++;
        lst = lst->next;
    }
}
*/
t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
    t_list  *new_list;
    t_list  *element;

    new_list = NULL;
    while (lst != NULL)
    {
        element = ft_lstnew((*f)(lst->content));
        if (element == NULL) 
        {
            ft_lstclear(&new_list, del);
            return NULL;
        }
        ft_lstadd_back(&new_list, element);
        lst = lst->next;
    }
    return (new_list);
}
// storing modified one in the new_list
// kalo gagal langsung delete the new list
// pertama, modify konten
// kedua pindah ke node yang baru
// ketiga lanjut ke next
// kalo gagal, masuk ke lst clear 
/*
void *multiple(void *content) 
{
    // free(content);
    (*(char *)content) = 'd' + 1;
    return content;
}

void del(void *content) 
{
    // free(content);
    (*(char *)content) = 'd';
}

void print_content(void *content) {
    printf("%c", (*(char *)content));
}

int main()
{
    // create a content to be freed
    char *a = malloc(1);
    char *b = malloc(1);
    t_list *result;
    *a = 'a';
    *b = 'b';

    // create a node to delete
    t_list *list = ft_lstnew(a);
    ft_lstadd_back(&list, ft_lstnew(b));

    ft_lstprint(list, &print_content);

    // call the func to delete node
    result = ft_lstmap(list, &multiple, &del);

    ft_lstprint(result, &print_content);

    //printf("after delete: %c, %c", *a, *b);
}
*/