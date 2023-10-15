/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansulist <ansulist@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:32:42 by ansulist          #+#    #+#             */
/*   Updated: 2023/10/14 11:50:26 by ansulist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	free_command_struct(t_cmdop *cmd, int size_command)
{
	int	i;

	i = 0;
	while (i < size_command)
	{
		if (cmd[i].name != NULL)
		{
			free(cmd[i].name);
		}
		if (cmd[i].args != NULL)
			free_two_d_array(cmd[i].args);
		i++;
	}
	free(cmd);
	return (0);
}

void	free_everything(t_env *env)
{
	if (env->origin != NULL)
		free_command_struct(env->origin, env->nb_struct);
	if (env->fd_in == true)
		close(STDIN_FILENO);
	if (env->fd_out == true)
		close(STDOUT_FILENO);	
	free_env(env);
}
