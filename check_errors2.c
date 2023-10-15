/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansulist <ansulist@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 18:58:50 by Famahsha          #+#    #+#             */
/*   Updated: 2023/10/15 11:22:28 by ansulist         ###   ########.fr       */
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

int	check_quotecount(char *str)
{
	char	firstquote;
	bool	insidequote;

	firstquote = '\0';
	insidequote = false;
	while (*str)
	{
		if (*str == '"' || *str == '\'')
		{
			if (firstquote == '\0')
				firstquote = *str;
			if (*str == firstquote)
				insidequote = !insidequote;
			else
			{
				if (!insidequote)
					return (-1);
			}
		}
		str++;
	}
	if (insidequote)
		return (1);
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

char	*remove_quotes(char *str)
{
	char	firstchar;
	bool	insidequotes;
	char	*readptr;
	char	*writeptr;

	firstchar = '\0';
	insidequotes = false;
	readptr = str;
	writeptr = str;
	while (*readptr)
	{
		if ((*readptr == '\'' || *readptr == '\"') && !insidequotes)
		{
			firstchar = *readptr;
			insidequotes = true;
		}
		else if (*readptr == firstchar && insidequotes)
			insidequotes = false;
		else
			*writeptr++ = *readptr;
		readptr++;
	}
	*writeptr = '\0';
	return (str);
}
