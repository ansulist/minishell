/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anitasulistiyawati <anitasulistiyawati@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 17:12:15 by asulisti          #+#    #+#             */
/*   Updated: 2022/11/15 12:05:58 by anitasulist      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t length)
{
	char	*d;
	char	*s;
	size_t	i;

	if (dst == src)
		return (dst);
	d = (char *)dst;
	s = (char *)src;
	if (s < d)
	{
		i = 0;
		while (i < length)
		{
			d[length - 1 - i] = s[length - 1 - i];
			i++;
		}
		return (dst);
	}
	i = 0;
	while (i < length)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}
// fungsi ini berguna untuk 
