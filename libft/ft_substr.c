/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Famahsha < famahsha@student.42abudhabi.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 17:19:30 by asulisti          #+#    #+#             */
/*   Updated: 2023/10/10 14:06:46 by Famahsha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	get_target_len(size_t s_len, unsigned int start)
{
	if (s_len < (size_t)start)
		return (0);
	return (s_len - start);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	char			*newstring;
	size_t			target_len;

	if (s == NULL)
		return (NULL);
	target_len = get_target_len(ft_strlen(s), start);
	if (len > target_len)
		len = target_len;
	if (len < target_len)
		target_len = len;
	newstring = malloc(sizeof(char) * target_len + 1);
	if (newstring == 0)
		return (0);
	i = start;
	while (s[i] != '\0' && len > 0)
	{
		newstring[i - start] = s[i];
		i++;
		len--;
	}
	newstring[i - start] = '\0';
	return (newstring);
}
/*
int main (void)
{
    char str[] = "anita";
    char *newstring;
    newstring = ft_substr(str, 2, 2);
    printf ("%s", newstring);
}
*/
