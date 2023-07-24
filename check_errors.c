/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansulist <ansulist@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 12:51:15 by Famahsha          #+#    #+#             */
/*   Updated: 2023/07/19 14:59:24 by ansulist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_piperror(char *str)
{
	int	i;

	i = 0;
	if (check_pipes(str[0]))
		return (ft_error(), 1);
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
		if (check_endline(str) == 1 || check_quotecount(str) == 1)
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

void	check_syntaxerror(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != '\0')
	{
		if (check_conditions(str, i))
			break ;
		if (1 == check_redirection(str[i]))
		{
			j = i + 1;
			if (check_quotes(str[j]))
			{
				j++;
				while (str[j] != '\0')
					j++;
				if (str[j] == '\0' && !check_quotes(str[j - 1]))
					ft_error();
			}
			if (check_redirection(str[j]) || ft_isspace(str[j]))
				j++;
			if (1 == check_redirection(str[j]) || (1 == check_pipes(str[j + 1])))
				ft_error();
			i = j;
		}
		else
			i++;
	}
}










// int check_semicolumn(char *str)
// {
// 	int i;
// 	int j;

// 	i = 0;
	
// 	while ( str[i])
// 	{
// 		if (str[i] == ';')
// 		{
// 			i++;
// 			if (ft_isspace(str[i]))
//                 i++;
// 			// if (str[j] == ';' || str[j] == '|')
// 			else
// 				return(ft_error(), 1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }