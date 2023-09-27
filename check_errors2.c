/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Famahsha < famahsha@student.42abudhabi.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 18:58:50 by Famahsha          #+#    #+#             */
/*   Updated: 2023/08/01 20:22:50 by Famahsha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_piperror(char *str)
{
	int	i;

	i = 0;
	if (check_pipes(str[0]))
	{
		return (ft_error(), 1);
	}
	while (ft_isspace(str[i]))
		i++;
	if (check_pipes(str[i]))
		return (ft_error(), 1);
	return (0);
}

int	check_endline(char *str)
{
	int	i;

	i = 0;
	if (check_piperror(str))
		return (1);
	while (str[i])
	{
		if (check_pipes(str[strlen(str) - 1])
			|| check_redirection(str[strlen(str) - 1]))
			return (ft_error(), 1);
		if (check_pipes(str[i]) || check_redirection(str[i]))
		{
			i++;
			if (ft_isspace(str[i]) == 1 && str[i + 1] == '\0')
				return (ft_error(), 1);
		}
		i++;
	}
	return (0);
}

void	remove_quotes(char *str)
{
	char	*newstr;

	newstr = str;
	while (*str)
	{
		if (*str != '\"' && (*str != '\''))
		{
			*newstr++ = *str;
		}
		str++;		
	}
	*newstr = '\0';
}