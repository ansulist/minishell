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

int    ft_free_twod_array(char **str)
{
    int i;

    i = 0;
    if (str == NULL)
        return -1;
    while (str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
    return (0);
}

char **ft_order_alpha(t_env *env)
{
    char **order;
    char *tmp;
    int i;
    int len;

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

// displaying "declare -x " in the first lien of every files in env
int print_export(t_env *env)
{
    int i;
    char **order;

    i = 0;
    order = ft_order_alpha(env);
    if (order == NULL)
        return -1;
    while (order[i])
    {
        ft_putstr_fd("declare -x ", 1);
        ft_putstr_fd(order[i], 1);
        ft_putstr_fd("\n", 1);
        i++;
    }
    ft_free_twod_array(order);
    return (0);
}
// print it each by each till the end
// int display_export(t_env *env)
// {
//     ft_order_alpha(env);
//     ft_lstiter(env->vars, &print_export);
//     return (0);
// }

int ft_add_update_loop(t_env *env, char *key, char **args)
{
    int i;
    char *tmp;

    i = 0;
    if (args == NULL || key == NULL)
        return (-1);
    while (args[i] != NULL)
    {
        tmp = getkey(args[i]);
        add_or_update(env, key, args[i]);
        free(tmp);
        i++;
    }
    return (0);
}

int	ft_export(t_env *env, char *cmd, char **args)
{
    printf("here   dscs\n");
	if (ft_strcmp(cmd, "export") == 0 && args[0] == NULL)
		print_export(env);
    if (ft_strcmp(cmd, "export") == 0 && args[0] != NULL)
        ft_add_update_loop(env, cmd, args);
    return (0);
}