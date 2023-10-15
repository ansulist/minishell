/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansulist <ansulist@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:52:55 by Famahsha          #+#    #+#             */
/*   Updated: 2023/10/14 11:56:02 by ansulist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*init_env(char **default_env)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (env == NULL)
		return (NULL);
	env->nb_struct = 0;
	env->origin = NULL;
	env->result = 0;
	env->fd_in = false;
	env->fd_out = false;
	env->vars = ft_2d_arr_to_list(default_env);
	if (env->vars == NULL)
	{
		free(env);
		return (NULL);
	}
	return (env);
}

void	display(void *content)
{
	if (content == NULL)
	{
		return ;
	}
	ft_putstr_fd((char *)content, 1);
	ft_putstr_fd("\n", 1);
}

int	display_env(t_env *env)
{
	ft_lstiter(env->vars, &display);
	return (0);
}

int	add_env_variable(t_env *env, char *key, char *value)
{
	t_list	*new_var;
	char	*content;

	content = ft_strjoin_3(key, "=", value);
	if (content == NULL)
	{
		return (-1);
	}
	new_var = ft_lstnew(content);
	if (new_var == NULL)
	{
		free(content);
		return (-1);
	}
	ft_lstadd_back(&env->vars, new_var);
	return (0);
}

void	delete_env_variable_free(void *content)
{
	free(content);
}
