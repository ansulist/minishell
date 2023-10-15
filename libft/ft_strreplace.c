/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansulist <ansulist@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:59:30 by Famahsha          #+#    #+#             */
/*   Updated: 2023/10/12 22:50:05 by ansulist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_result_len(char *str, char *to_replace, char *replace)
{
	int	i;
	int	result_len;
	int	to_replace_len;
	int	replace_len;

	to_replace_len = ft_strlen(to_replace);
	replace_len = ft_strlen(replace);
	result_len = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (ft_strncmp(str + i, to_replace, to_replace_len) == 0)
		{
			result_len += replace_len;
			i += to_replace_len;
		}
		else
		{
			result_len++;
			i++;
		}
	}
	return (result_len);
}

char	*prepare_stringer(char *str, char *to_replace, char *replace)
{
	int		result_len;
	char	*result;

	if (str == NULL)
		return (NULL);
	result_len = get_result_len(str, to_replace, replace);
	result = malloc(result_len + 1);
	return (result);
}

void	increase_loop(int *i, int *j)
{
	(*j)++;
	(*i)++;
}

char	*ft_strreplace(char *str, char *to_replace, char *replace)
{
	int		i;
	int		j;
	char	*result;

	result = prepare_stringer(str, to_replace, replace);
	if (result == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (ft_strncmp(str + i, to_replace, ft_strlen(to_replace)) == 0)
		{
			ft_strncpy(result + j, replace, ft_strlen(replace));
			j += ft_strlen(replace);
			i += ft_strlen(to_replace);
		}
		else
		{
			result[j] = str[i];
			increase_loop(&j, &i);
		}
	}
	result[(get_result_len(str, to_replace, replace))] = '\0';
	return (result);
}
