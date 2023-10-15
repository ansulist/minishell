/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirecspace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Famahsha < famahsha@student.42abudhabi.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:37:26 by Famahsha          #+#    #+#             */
/*   Updated: 2023/10/13 14:07:04 by Famahsha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_myisspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\f' || c == '\v')
		return (1);
	return (0);
}

char	*ft_mystrchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (NULL);
}

int	count_red(char *string, char *special_chars)
{
	int	count;

	count = 0;
	while (*string)
	{
		if (ft_mystrchr(special_chars, *string))
			count++;
		string++;
	}
	return (count);
}

char	*process_special_chars(char *str, char *special_chars)
{
	char	*temp;
	char	*result;

	temp = malloc((ft_strlen(str) + (2 * count_red(str, special_chars)) + 1));
	result = temp;
	while (*str)
	{
		if (ft_mystrchr(special_chars, *str))
		{
			*temp++ = ' ';
			if (ft_mystrchr(special_chars, *(str + 1)))
				*temp++ = *str;
			*temp++ = *str;
			while (*(str + 1) && ft_mystrchr(special_chars, *(str + 1)))
				str++;
			if (*(str + 1) && (!ft_myisspace(*(str + 1))))
				*temp++ = ' ';
		}
		else
			*temp++ = *str;
		str++;
	}
	*temp = '\0';
	return (result);
}
