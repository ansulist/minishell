/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansulist <ansulist@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:32:42 by ansulist          #+#    #+#             */
/*   Updated: 2023/09/08 16:18:33 by ansulist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO make a function to count the real struct after it is being made

int	free_two_d_array(char **av)
{
	int	i;

	i = 0;
	while (av[i] != NULL)
	{
		free(av[i]);
		i++;
	}
	free(av);
	return (0);
}

int	free_command_struct(t_cmdop *cmd)
{
	int	i;
	int nb_struct;

	nb_struct = count_struct(cmd->args);
	i = 0;
	while(i < nb_struct)
	{
		free(cmd->name);
		free_two_d_array(cmd->args);
		i++;
	}
	return (0);
}