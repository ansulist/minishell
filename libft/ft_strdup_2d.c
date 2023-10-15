/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_2d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Famahsha < famahsha@student.42abudhabi.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:54:48 by Famahsha          #+#    #+#             */
/*   Updated: 2023/10/10 13:56:58 by Famahsha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strdup_2d(char **arr)
{
	int		i;
	char	**arr_dup;

	i = ft_strlen_2d(arr);
	arr_dup = malloc(sizeof(char *) * (i + 1));
	if (arr_dup == NULL)
		return (NULL);
	i = 0;
	while (arr[i] != NULL)
	{
		arr_dup[i] = ft_strdup(arr[i]);
		if (arr_dup[i] == NULL)
		{
			while (i - 1 >= 0)
			{
				free(arr_dup[i - 1]);
				i--;
			}
			return (NULL);
		}
		i++;
	}
	return (arr_dup);
}
