/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_spaces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Famahsha < famahsha@student.42abudhabi.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:38:42 by Famahsha          #+#    #+#             */
/*   Updated: 2023/10/13 16:03:52 by Famahsha         ###   ########.fr       */
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
		if (*string == '|' && ft_strlen(string) != 1)
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
