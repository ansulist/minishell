/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_remove_if.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansulist <ansulist@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:52:58 by Famahsha          #+#    #+#             */
/*   Updated: 2023/10/11 23:08:30 by ansulist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	remove_and_attach(t_list **current, t_list **previous,
		t_list **begin_list, void (*del)(void *))
{
	t_list	*tmp;

	tmp = (*current)->next;
	del((*current)->content);
	free(*current);
	if ((*previous) == NULL)
		*begin_list = tmp;
	else
		(*previous)->next = tmp;
	*current = tmp;
}

void	ft_lst_remove_if(t_list **begin_list, void *data_ref,
		int (*cmp)(void *, void *), void (*del)(void *))
{
	t_list	*current;
	t_list	*previous;

	if ((begin_list == NULL) || (*begin_list == NULL))
		return ;
	previous = NULL;
	current = *begin_list;
	while (current != NULL)
	{
		if (cmp(current->content, data_ref) == 0)
			remove_and_attach(&current, &previous, begin_list, del);
		else
		{
			previous = current;
			current = current->next;
		}
	}
}
