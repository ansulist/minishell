/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Famahsha < famahsha@student.42abudhabi.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:58:34 by Famahsha          #+#    #+#             */
/*   Updated: 2023/10/10 13:59:00 by Famahsha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_3(char *str1, char *str2, char *str3)
{
	int		len1;
	int		len2;
	int		len3;
	char	*result;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	len3 = ft_strlen(str3);
	result = malloc(len1 + len2 + len3 + 1);
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, str1, len1 + 1);
	ft_strlcpy(result + len1, str2, len2 + 1);
	ft_strlcpy(result + len1 + len2, str3, len3 + 1);
	result[len1 + len2 + len3] = '\0';
	return (result);
}
