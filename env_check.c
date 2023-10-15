/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Famahsha < famahsha@student.42abudhabi.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:54:33 by Famahsha          #+#    #+#             */
/*   Updated: 2023/10/10 14:16:13 by Famahsha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	delete_env_variable_cmp(void *content, void *key)
{
	return (ft_strncmp((char *)content, (char *)key, ft_strlen((char *)key)));
}

void	delete_env_variable(t_env *env, char *key)
{
	ft_lst_remove_if(&env->vars, key, &delete_env_variable_cmp,
		&delete_env_variable_free);
}

int	cmp_var(void *s1, void *s2)
{
	return (ft_strncmp((char *)s1, (char *)s2, ft_strlen((const char *)s2)));
}
