/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Famahsha < famahsha@student.42abudhabi.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:19:32 by Famahsha          #+#    #+#             */
/*   Updated: 2023/10/08 14:06:44 by Famahsha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_free_twod_array(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (-1);
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (0);
}

char	**ft_order_alpha(t_env *env)
{
	char	**order;
	char	*tmp;
	int		i;
	int		len;

	i = 0;
	len = ft_lstsize(env->vars);
	order = ft_list_to_array(env->vars);
	if (order == NULL)
		return (NULL);
	while (i < len - 1)
	{
		if (ft_strcmp(order[i], order[i + 1]) > 0)
		{
			tmp = order[i];
			order[i] = order[i + 1];
			order[i + 1] = tmp;
			i = -1;
		}
		i++;
	}
	return (order);
}
