/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Famahsha < famahsha@student.42abudhabi.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 10:48:44 by ansulist          #+#    #+#             */
/*   Updated: 2023/10/08 13:54:13 by Famahsha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_env_variable(t_list *var, char *key, char *value)
{
	char	*tmp;

	tmp = ft_strjoin_3(key, "=", value);
	if (tmp == NULL)
		return (-1);
	free(var->content);
	var->content = tmp;
	return (0);
}

int	add_or_update(t_env *env, char *key, char *value)
{
	t_list	*var;

	var = ft_lstfind(env->vars, &cmp_var, key);
	if (var == NULL)
		return (add_env_variable(env, key, value));
	return (update_env_variable(var, key, value));
}

int	display_env_var(t_env *env, char *key)
{
	t_list	*var;

	var = ft_lstfind(env->vars, &cmp_var, key);
	if (var == NULL)
		return (-1);
	ft_putstr_fd((char *)(var->content) + ft_strlen(key) + 1, 1);
	return (0);
}

int	ft_env(t_env *env, t_cmdop *cmd)
{
	if (cmd[0].args[0] != NULL)
	{
		if (display_env_var(env, cmd[0].args[0]) == -1)
		{
			display_env(env);
			return (-1);
		}
	}
	if (cmd[0].args[0] == NULL)
	{
		if (display_env(env) == -1)
			return (-1);
	}
	return (0);
}
