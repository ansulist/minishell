/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansulist <ansulist@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:16:10 by Famahsha          #+#    #+#             */
/*   Updated: 2023/10/15 11:20:52 by ansulist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_non_nb_arg(t_env *env, int status)
{
	env->result = status;
	ft_putendl_fd("./minishell : args is not number", STDERR_FILENO);
}

int	ft_count_array(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != NULL)
		i++;
	return (i);
}

void	decide_result(t_cmdop *cmd, t_env *env)
{
	if (is_longlong(cmd->args[0]) == true)
		env->result = ft_atoi(cmd->args[0]);
	else
		exit_non_nb_arg(env, 255);
}

void	ft_exit(t_cmdop *cmd, t_env *env)
{
	int	nb_args;
	int	ret;

	nb_args = ft_count_array(cmd->args);
	ft_putendl_fd("exit minishell, bye!", STDOUT_FILENO);
	if (nb_args == 1)
	{
		if (digits_or_signals(cmd->args[0]) == true)
			decide_result(cmd, env);
		else
			exit_non_nb_arg(env, 255);
	}
	else if (nb_args > 1)
	{
		env->result = 2;
		ft_putendl_fd("./minishell : Too many argument", STDERR_FILENO);
	}
	ret = env->result;
	free_everything(env);
	exit(ret);
}
