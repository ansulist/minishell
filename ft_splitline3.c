/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitline3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansulist <ansulist@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:28:33 by Famahsha          #+#    #+#             */
/*   Updated: 2023/10/11 16:24:47 by ansulist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_dollarsign(t_cmdop *cmd, int len, t_env *env)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (i < len)
	{
		while (cmd[i].args[j])
		{
			if (ft_strncmp(cmd[i].args[j], "$", 1) == 0)
			{
				tmp = ft_strdup(cmd[i].args[j]);
				cmd[i].args[j] = my_getenv(env, cmd[i].args[j]);
				if (cmd[i].args[j] == NULL)
				{
					cmd[i].args[j] = tmp;
					free(tmp);
				}
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_free_command_struct(t_cmdop **command, int nb_struct)
{
	int	i;

	i = 0;
	while (i < nb_struct)
	{
		if (command[i]->name != NULL)
			free(command[i]->name);
		if (command[i]->args != NULL)
			ft_free_twod_array(command[i]->args);
		i++;
	}
	return (0);
}

int	free_and_return(char **av, t_cmdop **command, int ret_val, int nb_struct)
{
	ft_free_twod_array(av);
	if (command != NULL)
		ft_free_command_struct(command, nb_struct);
	return (ret_val);
}

int	init_struct(char *str, t_cmdop **command)
{
	int		nb_struct;
	char	**av;

	av = ft_newsplit(str, ' ');
	if (av == NULL)
		return (-1);
	nb_struct = count_struct(av);
	if (nb_struct == 0)
		return (free_and_return(av, NULL, 0, nb_struct));
	*command = ft_calloc(nb_struct, sizeof(t_cmdop));
	if (*command == NULL)
		return (free_and_return(av, NULL, -1, nb_struct));
	if (fill_structs(av, *command) == -1)
		return (free_and_return(av, command, -1, nb_struct));
	ft_free_twod_array(av);
	return (nb_struct);
}
