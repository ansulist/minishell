/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anitasulistiyawati <anitasulistiyawati@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 17:35:30 by asulisti          #+#    #+#             */
/*   Updated: 2022/01/25 11:59:22 by anitasulist      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memcpy(void *dest, const void *src, size_t length)
{
	size_t	i;

	i = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (i < length)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return (dest);
}
//fungsi ini berguna untuk menyalin memori dari src ke dest.
// warning : fungsi ini tidak menghandle overlap!!
/*
int main (void)
{
    char arrayA[3] = "akk";
    char arrayB[3];
    ft_memcpy(arrayB, arrayA, 5);
    printf("%c, %c, %c", arrayB[0], arrayB[1], arrayB[2]);
}
*/
