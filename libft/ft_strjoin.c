/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anitasulistiyawati <anitasulistiyawati@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 12:37:30 by asulisti          #+#    #+#             */
/*   Updated: 2022/11/18 12:22:47 by anitasulist      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*str_res;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	str_res = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (str_res == NULL)
		return (NULL);
	ft_memmove(str_res, s1, ft_strlen(s1));
	ft_memmove(str_res + ft_strlen(s1), s2, ft_strlen(s2));
	str_res[(ft_strlen(s1) + ft_strlen(s2))] = '\0';
	return (str_res);
}
