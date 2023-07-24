/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansulist <ansulist@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 10:48:44 by ansulist          #+#    #+#             */
/*   Updated: 2023/07/18 13:47:45 by ansulist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env *init_env(char **default_env) {
    t_env *env;

    env = malloc(sizeof(env));
    if (env == NULL) {
        return (NULL);
    }
    
    env->vars = ft_2d_arr_to_list(default_env);
    if (env->vars == NULL) {
        free(env);
        return (NULL);
    }

    return (env);
}

void display(void *content)
{
    if (content == NULL) {
        return;
    }
    ft_putstr_fd((char *)content, 1);
    ft_putstr_fd("\n", 1);
}

int display_env(t_env *env)
{
    ft_lstiter(env->vars, &display);
	return (0);
}

int add_env_variable(t_env *env, char *key, char *value)
{
    t_list *new_var;
    char *content;

    content = ft_strjoin_3(key, "=", value);
    if (content == NULL) {
        return (-1);
    }
    new_var = ft_lstnew(content);
    if (new_var == NULL) {
        free(content);
        return (-1);
    }
    ft_lstadd_back(&env->vars, new_var);
    return (0);
}

void delete_env_variable_free(void *content)
{
    free(content);
}

int delete_env_variable_cmp(void *content, void *key)
{
    return ft_strncmp((char *)content, (char *)key, ft_strlen((char *)key));
}

void delete_env_variable(t_env *env, char *key)
{
    ft_lst_remove_if(&env->vars, key, &delete_env_variable_cmp, &delete_env_variable_free);
}

int cmp_var(void *s1, void *s2)
{
    return (ft_strncmp((char *)s1, (char *)s2, ft_strlen((const char *)s2)));
}

int update_env_variable(t_list *var, char *key, char *value)
{
    char *tmp;

    tmp = ft_strjoin_3(key, "=", value);
    if (tmp == NULL)
        return (-1);
    free(var->content);
    var->content = tmp;
    return (0);
}

int add_or_update(t_env *env, char *key, char *value)
{
    t_list *var;

    var = ft_lstfind(env->vars, &cmp_var, key);
    if (var == NULL)
        return (add_env_variable(env, key, value));
    return (update_env_variable(var, key, value));
}

int    display_env_var(t_env *env, char *key)
{
    t_list *var;

    var = ft_lstfind(env->vars, &cmp_var, key);
    if (var == NULL)
        return -1;
    ft_putstr_fd((char *)(var->content) + ft_strlen(key) + 1, 1);
    return (0);
}

int	ft_env(t_env *env, t_cmdop *cmd)
{
	//only accepting after the "$" is removed
	//needs a func o remove the $ from the key in parsing
	// if the args not match with the key in env
	// just display the regular env
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