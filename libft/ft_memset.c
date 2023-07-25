/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anita <anita@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 17:12:29 by asulisti          #+#    #+#             */
/*   Updated: 2022/01/04 19:46:42 by anita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *mem, int c, size_t lenght)
{
	size_t	i;

	i = 0;
	while (i < lenght)
	{
		((char *)mem)[i] = c;
		i++;
	}
	return (mem);
}
/*
fungsi ini berguna untuk mengisi memori dengan angka atau things yang d butuhkan
int main()
{
    char arr[4];
    ft_memset(arr, 0, 4);
    printf("%d %d %d %d", arr[0], arr[1], arr[2], arr[3]);
}
*/
