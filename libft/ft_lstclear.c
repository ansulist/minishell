/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Famahsha < famahsha@student.42abudhabi.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 00:53:29 by anitasulist       #+#    #+#             */
/*   Updated: 2023/10/10 14:02:06 by Famahsha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*link_saver;

	if (lst == NULL || *lst == NULL)
		return ;
	while (*lst != NULL)
	{
		link_saver = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = link_saver;
	}
}
/*
// fungsi ini berguna untuk menghapus seluruh konten node
// dan node itu sendiri yang ada dalam link

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
	char *b = malloc(1);
	*a = 'a';
	*b = 'b';

	// create a node to delete
	t_list *list = ft_lstnew(a);
	ft_lstadd_back(&list, ft_lstnew(b));

	// call the func to delete node
	ft_lstclear(&list, &delete);

	printf("after delete: %c, %c", *a, *b);
}
*/