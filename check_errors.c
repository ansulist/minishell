/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Famahsha < famahsha@student.42abudhabi.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 12:51:15 by Famahsha          #+#    #+#             */
/*   Updated: 2023/08/01 20:55:15 by Famahsha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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

// int	check_consecquotes(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] =='\'')
// 		{
// 			if (ft_isspace(str[i + 1]))
// 				perror(str);
// 			else if (str[i + 1] == '\"')
// 				perror(str);
// 			return (-1);
// 		}			
// 		else if (str[i] =='\"')
// 		{
// 			if (ft_isspace(str[i + 1]))
// 				perror(str);
// 			else if (str[i + 1] == '\'')
// 				perror(str);
// 			return (-1);
// 		}
// 		else
// 			i++;
// 	}
// 	return (0);
// }

int	check_consecquotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] =='\'')
		{
			if (ft_isspace(str[i + 1]))
				return (-1);
			if (str[i + 1] == '\"')
				return(-1);
		}
		else if (str[i] =='\"')
		{
			if (ft_isspace(str[i + 1]))
				return (-1);
			if (str[i + 1] == '\'')
				return (-1);
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
	// printf("hello \n");
	while (str[i] != '\0')
	{
		if (check_conditions(str, i))
		{
			return (1);
			// break ;
		}
		if (1 == check_redirection(str[i]))
		{
			j = i + 1;
			if (check_quoteasafterred(str, j))
				return (ft_error(), 1);
			if (check_redirection(str[j]) == 1)
				j++;
			while (ft_isspace(str[j]))
				j++;
			if (1 == check_redirection(str[j])
				|| str[j] == '\0' || (1 == check_pipes(str[j + 1])))
				return (ft_error(), 1);
			i = j;
		}
		else
			i++;
	}
	return (0);
}


// after j = i  +1;
//  if (check_quotes(str[j])) 
			// {
			// 	j++;
			// 	while (str[j] != '\0')
			// 		j++;
			// 	if (str[j] == '\0' && !check_quotes(str[j - 1]))
			// 		ft_error();
			// }




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