/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Famahsha < famahsha@student.42abudhabi.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:29:28 by Famahsha          #+#    #+#             */
/*   Updated: 2023/10/13 14:06:09 by Famahsha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bye_minishell(t_env *env)
{
	printf("exit -> bye, Minishell");
	free_env(env);
	exit(0);
}

int	check_spaces(char *str)
{
	while (*str)
	{
		if (!ft_isspace(*str))
			return (0);
		str++;
	}
	return (1);
}

int	one_heredoc(t_cmdop *command_line)
{
	char	*buff;

	while (1)
	{
		buff = readline("> ");
		if (buff == NULL)
		{
			return (-1);
		}
		if (arestringsequal(buff, command_line->name) == true)
			return (0);
	}
	free(buff);
}
