/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitline2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Famahsha < famahsha@student.42abudhabi.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:27:09 by Famahsha          #+#    #+#             */
/*   Updated: 2023/10/13 13:55:05 by Famahsha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_command(char **av, t_cmdop *command, int *i)
{
	int	k;

	command->name = ft_strdup(av[*i]);
	if (command->name == NULL)
		return (-1);
	remove_quotes(command->name);
	(*i)++;
	k = *i;
	while (av[k] != NULL && is_operator(av[k]) == NONE)
		k++;
	command->nb_args = k - *i;
	command->args = malloc(sizeof(char *) * (k - *i + 1));
	if (command->args == NULL)
		return (-1);
	return (fill_command_args(av, command, i));
}

int	command_set_op_and_name(t_cmdop *command, t_op op, char *name)
{
	command->operator = op;
	command->name = ft_strdup(name);
	remove_quotes(command->name);
	if (command->name == NULL)
		return (-1);
	return (0);
}

int	fill_struct(char **av, t_cmdop *command, int *i)
{
	t_op	op;

	op = is_operator(av[*i]);
	if (op == NONE)
	{
		if (fill_command(av, command, i) == -1)
			return (-1);
		return (0);
	}
	if (op == PIPE)
	{
		command->operator = PIPE;
		(*i)++;
		return (0);
	}
	if (command_set_op_and_name(command, op, av[*i + 1]) == -1)
		return (-1);
	*i += 2;
	return (0);
}

int	fill_structs(char **av, t_cmdop *command)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (av[i] != NULL)
	{
		if (fill_struct(av, &command[j], &i) == -1)
			return (-1);
		j++;
	}
	return (0);
}
