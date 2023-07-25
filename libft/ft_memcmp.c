/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anita <anita@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 18:21:27 by asulisti          #+#    #+#             */
/*   Updated: 2022/01/04 19:45:13 by anita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*(const unsigned char *)(s1 + i)
			!= *(const unsigned char *)(s2 + i))
			return (*(const unsigned char *)(s1 + i)
			- *(const unsigned char *)(s2 + i));
		i++;
	}
	return (0);
}
/*
int main (void)
{
    printf ("%d", ft_memcmp("hello", "hella", 5));
}
*/
