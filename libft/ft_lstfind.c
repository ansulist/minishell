/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansulist <ansulist@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:02:56 by Famahsha          #+#    #+#             */
/*   Updated: 2023/10/11 11:30:36 by ansulist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstfind(t_list *list, int (cmp)(void *, void *), void *data_ref)
{
	while (list != NULL)
	{
		if (cmp(list->content, data_ref) == 0)
			return (list);
		list = list->next;
	}
	return (NULL);
}
