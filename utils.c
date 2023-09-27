/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Famahsha < famahsha@student.42abudhabi.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 16:57:58 by Famahsha          #+#    #+#             */
/*   Updated: 2023/07/15 13:26:20 by Famahsha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			n = s1[i] - s2[i];
			return (n);
		}
		else
			i++;
	}
	return (n);
}

int	check_redirection(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

int	check_quotes(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	check_pipes(char c)
{
	if (c == '|')
		return (1);
	return (0);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\f' || c == '\v')
		return (1);
	return (0);
}
