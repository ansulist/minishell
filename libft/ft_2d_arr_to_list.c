/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2d_arr_to_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Famahsha < famahsha@student.42abudhabi.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:51:02 by Famahsha          #+#    #+#             */
/*   Updated: 2023/10/10 13:51:24 by Famahsha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	del(void *content)
{
	if (content != NULL)
	{
		free(content);
	}
}

t_list	*ft_2d_arr_to_list(char **arr)
{
	t_list	*list;
	t_list	*tmp;
	char	*content;
	int		i;

	list = NULL;
	i = 0;
	while (arr[i] != NULL)
	{
		content = ft_strdup(arr[i]);
		if (content == NULL)
		{
			ft_lstclear(&list, &del);
			return (NULL);
		}
		tmp = ft_lstnew(content);
		if (tmp == NULL)
		{
			ft_lstclear(&list, &del);
			return (NULL);
		}
		ft_lstadd_back(&list, tmp);
		i++;
	}
	return (list);
}
