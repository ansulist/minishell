/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_to_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansulist <ansulist@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:51:31 by Famahsha          #+#    #+#             */
/*   Updated: 2023/10/11 11:20:50 by ansulist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*free_2d_array_n(char **array, int i)
{
	while (i >= 0)
	{
		free(array[i]);
		i--;
	}
	free(array);
	return (NULL);
}

char	**ft_list_to_array(t_list *list)
{
	t_list	*tmp;
	char	**array;
	int		i;

	tmp = list;
	i = 0;
	array = malloc(sizeof(char *) * (ft_lstsize(list) + 1));
	if (array == NULL)
		return (NULL);
	while (tmp != NULL)
	{
		array[i] = ft_strdup((char *)(tmp->content));
		if (array[i] == NULL)
		{
			i--;
			free_2d_array_n(array, i);
			return (NULL);
		}
		tmp = tmp->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}
