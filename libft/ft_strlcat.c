/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anitasulistiyawati <anitasulistiyawati@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 17:11:11 by asulisti          #+#    #+#             */
/*   Updated: 2022/11/18 12:28:26 by anitasulist      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	end;

	if (!dest && !size)
		return (0);
	end = ft_strlen(dest);
	if (size <= end)
		return (size + ft_strlen(src));
	i = 0;
	while (src[i] != '\0' && i < size - end - 1)
	{
		dest[end + i] = src[i];
		i++;
	}
	dest[end + i] = '\0';
	return (ft_strlen(src) + end);
}
/*
int main()
{
	printf("result = %zu", ft_strlcat("\0", NULL, 0));
	printf("result = %lu", strlcat("\0", "\0", 0));
}
*/