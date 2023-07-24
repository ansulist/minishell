/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansulist <ansulist@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 10:49:03 by ansulist          #+#    #+#             */
/*   Updated: 2023/07/13 11:53:11 by ansulist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// displaying "declare -x " in the first lien of every files in env
void print_export(void *content)
{
    if (content == NULL) {
        return;
    }
	ft_putstr_fd("declare -x ", 1);
    ft_putstr_fd((char *)content, 1);
    ft_putstr_fd("\n", 1);
}

// print it each by each till the end
int display_export(t_env *env)
{
    ft_lstiter(env->vars, &print_export);
    return (0);
}

int ft_add_update_loop(t_env *env, char *key, char **args)
{
    int i;

    i = 0;
    if (args == NULL || key == NULL)
        return (-1);
    while (args[i] != NULL)
    {
        add_or_update(env, key, args[i]);
        i++;
    }
    return (0);
}

int	ft_export(t_env *env, char *cmd, char **args)
{
	if (ft_strcmp(cmd, "export") == 0 && args == NULL)
		display_export(env);
    else if (ft_strcmp(cmd, "export") == 0 && args != NULL)
        ft_add_update_loop(env, cmd, args);
    return (0);
}