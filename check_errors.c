/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Famahsha < famahsha@student.42abudhabi.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 12:51:15 by Famahsha          #+#    #+#             */
/*   Updated: 2023/10/13 15:06:31 by Famahsha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_quoted_string(const char *s, int i)
{
	char	c;

	if ((s[i] == 39 || s[i] == 34))
	{
		c = s[i];
		i++;
		while (s[i] != c && s[i])
			i++;
	}
	return (i);
}

int	skip_quote(char *str, int i)
{
	while (check_quotes(str[i]) != 1)
		i++;
	i++;
	return (i);
}

int	check_conditions(char *str, int i)
{
	int	k;

	k = 1;
	while (str[i] != '\0')
	{
		if (check_quotecount(str) == 1)
			return (ft_error(), 1);
		if (check_endline(str) == 1)
			return (1);
		if (check_quotes(str[i]) == 1)
		{
			i = skip_quote(str, i++);
			return (0);
		}
		if (1 == check_pipes(str[i]))
		{
			k = i + 1;
			while (ft_isspace(str[k]))
				k++;
			if (1 == check_pipes(str[k]) || str[k] == ';')
				return (ft_error(), 1);
		}
		i++;
	}
	return (0);
}

int	check_quoteasafterred(char *str, int j)
{
	if (check_quotes(str[j]))
	{
		j++;
		while (str[j] != '\0')
			j++;
		if (str[j] == '\0' && !check_quotes(str[j - 1]))
			return (1);
	}
	return (0);
}

int	check_syntaxerror(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != '\0')
	{
		if (check_conditions(str, i))
			return (1);
		if (1 == check_redirection(str[i]))
		{
			j = i + 1;
			if (check_quoteasafterred(str, j))
				return (ft_error(), 1);
			if (check_redirection(str[j]) == 1)
				j++;
			while (ft_isspace(str[j]))
				j++;
			if (check_redirection(str[j]) || !str[j] || check_pipes(str[j + 1]))
				return (ft_error(), 1);
			i = j;
		}
		else
			i++;
	}
	return (0);
}
