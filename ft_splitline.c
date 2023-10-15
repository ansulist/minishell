/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Famahsha < famahsha@student.42abudhabi.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:40:44 by Famahsha          #+#    #+#             */
/*   Updated: 2023/10/13 14:01:02 by Famahsha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_op	is_operator(char *str)
{
	if (str == NULL)
		return (NONE);
	if (str[0] == '|' && str[1] == '\0')
		return (PIPE);
	if (str[0] == '<' && str[1] == '\0')
		return (LEFT_REDIRECTION);
	if (str[0] == '<' && str[1] == '<' && str[2] == '\0')
		return (DOUBLE_LEFT_REDIRECTION);
	if (str[0] == '>' && str[1] == '\0')
		return (RIGHT_REDIRECTION);
	if (str[0] == '>' && str[1] == '>' && str[2] == '\0')
		return (DOUBLE_RIGHT_REDIRECTION);
	return (NONE);
}

void	count_struct_none(int *i, int *nb_struct, char **av)
{
	(*nb_struct)++;
	(*i)++;
	while (av[*i] != NULL && is_operator(av[*i]) == NONE)
		(*i)++;
}

void	count_struct_else(int *i, int *nb_struct)
{
	(*nb_struct)++;
	(*i) += 2;
}

int	count_struct(char **av)
{
	int		i;
	t_op	op;
	int		nb_struct;

	nb_struct = 0;
	i = 0;
	while (av[i] != NULL)
	{
		op = is_operator(av[i]);
		if (op == NONE)
			count_struct_none(&i, &nb_struct, av);
		else if (op == PIPE)
		{
			nb_struct++;
			i++;
		}
		else
			count_struct_else(&i, &nb_struct);
	}
	return (nb_struct);
}

int	fill_command_args(char **av, t_cmdop *command, int *i)
{
	int	k;

	k = 0;
	while (av[*i] != NULL && is_operator(av[*i]) == NONE)
	{
		command->args[k] = ft_strdup(av[*i]);
		if (command->args[k] == NULL)
			return (-1);
		remove_quotes(command->args[k]);
		k++;
		(*i)++;
	}
	command->args[k] = NULL;
	return (0);
}
