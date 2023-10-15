/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Famahsha < famahsha@student.42abudhabi.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 23:55:23 by ansulist          #+#    #+#             */
/*   Updated: 2023/10/10 14:12:54 by Famahsha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_valid_env_char(char c)
{
	if (c >= 'a' && c <= 'z')
		return (true);
	if (c >= 'A' && c <= 'Z')
		return (true);
	if (c >= '0' && c <= '9')
		return (true);
	if (c == '_')
		return (true);
	return (false);
}

int	count_nbr(int nbr)
{
	int	i;

	i = 0;
	if (nbr <= 0)
		return (1);
	if (nbr > 0)
	{
		while (nbr > 0)
		{
			nbr /= 10;
			i++;
		}
	}
	return (i);
}

int	count_dollar_var_len(char *line, t_env *env, int *i)
{
	int		end;
	char	*key;
	char	*env_var;
	int		var_len;

	var_len = 0;
	end = *i + 1;
	while (is_valid_env_char(line[end]))
		end++;
	if (end - *i - 1 == 0)
		return (1);
	key = ft_strndup(line + *i + 1, end - *i - 1);
	if (key == NULL)
		return (-1);
	*i = end - 1;
	env_var = my_getenv(env, key);
	free(key);
	if (env_var != NULL)
	{
		var_len = ft_strlen(env_var);
		free(env_var);
	}
	return (var_len);
}

void	look_for_closure(char *line, int *j, char c)
{
	(*j)++;
	while (line[*j] != c && line[*j] != '\0')
		(*j)++;
}

bool	ignore_env_var(char *line, int i)
{
	int	j;

	j = 0;
	while (line[j] != '\0')
	{
		if (line[j] == '\"')
		{
			look_for_closure(line, &j, '\"');
			if (line[j] == '\0' || i < j)
				return (false);
		}
		else if (line[j] == '\'')
		{
			look_for_closure(line, &j, '\'');
			if (line[j] == '\0')
				return (false);
			if (i < j)
				return (true);
		}
		else if (i == j)
			return (false);
		j++;
	}
	return (false);
}
