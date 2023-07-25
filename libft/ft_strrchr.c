/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anitasulistiyawati <anitasulistiyawati@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 17:18:50 by asulisti          #+#    #+#             */
/*   Updated: 2022/01/25 13:56:07 by anitasulist      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*ret;

	ret = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			ret = (char *)s + i;
		i++;
	}
	if (c == '\0')
		return ((char *)s + i);
	return (ret);
}
/*
// jadi kompare dari paling belakang termasuk \0
int main    (void)
{
    char s[] = "aku adalah anak gembala";
    char c = 'k';
    printf("%s", ft_strrchr(s, c));
}
*/
