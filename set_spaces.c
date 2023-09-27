/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_spaces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Famahsha < famahsha@student.42abudhabi.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:38:42 by Famahsha          #+#    #+#             */
/*   Updated: 2023/08/01 19:21:06 by Famahsha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipes(char *string)
{
	int	count;
	int	inside_quotes;

	count = 0;
	inside_quotes = 0;
	while (*string)
	{
		if (*string == '"')
			inside_quotes = !inside_quotes;
		if (*string == '|' && !inside_quotes)
			count++;
		string++;
	}
	return (count);
}

int	check_quotecount(char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (check_quotes(*str) == 1)
			count++;
		str++;
	}
	if (count % 2 != 0)
	{
		ft_error();
		return (1);
	}
	else
		return (count);
}

char	*rostring(char *string)
{
	int		count;
	char	*temp;
	char	*result;

	count = count_pipes(string);
	temp = (char *)malloc((ft_strlen(string) + (2 * count) + 1) * sizeof(char));
	result = temp;
	while (*string)
	{
		if (*string == '|')
		{
			if (!ft_isspace(*(string - 1)))
				*temp++ = ' ';
			*temp++ = '|';
			while (ft_isspace(*(string + 1)))
				string++;
			if (!ft_isspace(*(string + 1)))
				*temp++ = ' ';
		}
		else
			*temp++ = *string;
		string++;
	}
	*temp = '\0';
	return (result);
}
