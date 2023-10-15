/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Famahsha < famahsha@student.42abudhabi.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:58:53 by Famahsha          #+#    #+#             */
/*   Updated: 2023/10/13 15:49:19 by Famahsha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_one(char *line, t_env *env, t_fill_vars *vars)
{
	int		var_len;
	bool	ignore_env;

	ignore_env = ignore_env_var(line, vars->i);
	if (!ignore_env && line[vars->i] == '$' && line[vars->i + 1] == '?')
	{
		vars->counter += count_nbr(env->result);
		vars->i++;
		return (0);
	}
	if (!ignore_env && line[vars->i] == '$')
	{
		var_len = count_dollar_var_len(line, env, &vars->i);
		if (var_len == -1)
			return (-1);
		vars->counter += var_len;
		return (0);
	}
	vars->counter++;
	return (0);
}

int	counter(char *line, t_env *env)
{
	t_fill_vars	vars;

	vars.counter = 0;
	vars.i = 0;
	while (line[vars.i] != '\0')
	{
		if (count_one(line, env, &vars) == -1)
			return (-1);
		vars.i++;
	}
	return (vars.counter);
}
