/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anitasulistiyawati <anitasulistiyawati@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 17:19:17 by asulisti          #+#    #+#             */
/*   Updated: 2022/01/24 12:58:27 by asulisti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	fake_strchr(const char *s1, char c)
{
	int	i;

	i = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] == c)
			return (1);
		i++;
	}
	return (0);
}	

char	*ft_strtrim(char const *s1, char const *set)
{
	int	first;
	int	last;

	if (s1 == NULL || set == NULL)
		return (NULL);
	first = 0;
	while (s1[first] && fake_strchr(set, s1[first]))
	{
		first++;
	}
	last = ft_strlen(s1);
	while (last >= 0 && last != first && fake_strchr(set, s1[last - 1]))
	{
		last--;
	}
	return (ft_substr(s1, first, last - first));
}
/*
int main (void)
{
    printf("%s", ft_strtrim("dirinyadirinyadirinya 
	nitadirinyadirinyadirinya", "dirinya"));
}
*/
