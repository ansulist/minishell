/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Famahsha < famahsha@student.42abudhabi.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 01:42:58 by anitasulist       #+#    #+#             */
/*   Updated: 2023/10/10 14:03:53 by Famahsha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst != NULL)
	{
		(*f)(lst->content);
		lst = lst->next;
	}
}
/*
// fungsi ini berguna untuk mengaplikasikan
// fungsi yang diinginkan ke semua node yang ada

void multiple(void *content) {
	// free(content);
	(*(char *)content) = 'd' + 1;
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
	ft_lstiter(list, &multiple);

	printf("after delete: %c, %c", *a, *b);
}
*/