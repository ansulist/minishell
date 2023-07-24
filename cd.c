/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansulist <ansulist@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 10:48:25 by ansulist          #+#    #+#             */
/*   Updated: 2023/07/11 10:48:26 by ansulist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ft_move moves to the given path
// but ut doesnt handle home

//finding the value of every key in the env
char    *my_getenv(t_env *env, char *key)
{
    t_list *temp;

    temp = env->vars;
    while (temp != NULL)
    {
		// if it is match and next to it is '='
		// then copy the value and return it
        if (ft_strncmp(key, (char *)temp->content, ft_strlen(key)) == 0 && ((char *)temp->content)[ft_strlen(key)] == '=')
            return (ft_strdup(temp->content + ft_strlen(key) + 1));
        temp = temp->next;
    }
    return (NULL);
}

int ft_move(t_env *env, char *path)
{
    char *pwd;
    char *new_path;
    int ret;

    if (path == NULL)
        return (0);
    if (chdir(path) < 0)
    {
        perror(path);
        return (0);
    }
    new_path = getcwd(NULL, 0);
    if (new_path == NULL)
        return (-1);
    pwd = my_getenv(env, "PWD");
    ret = add_or_update(env, "PWD", new_path);
    if (ret != -1)
    {
        if (pwd == NULL)
            ret = add_or_update(env, "OLD_PWD", new_path);
        else
            ret = add_or_update(env, "OLD_PWD", pwd);
    }
    free(new_path);
    if (pwd != NULL)
        free(pwd);
    return (ret);
}

int ft_cd(t_env *env, char *path)
{
    char *home;
    char *oldpwd;
    int ret;
    char *replace;

    if (path == NULL || ft_strlen(path) == 0 || ft_strchr(path, '~') != 0)
    {
        home = my_getenv(env, "HOME");
        if (home == NULL)
            return (0);
        // only command cd do this
        if (path == NULL || ft_strlen(path) == 0)
            ret = ft_move(env, home);
        // if there is '~' somewhere
        else 
        {
            // changing the ~ with the home
            replace = ft_strreplace(path, "~", home);
            if (replace == NULL)
            {
                free(home);
                return (-1);
            }
            // then move to home
            ret = ft_move(env, replace);
            free(replace);
        }
        free(home);
        return (ret);
    }
    // if there is '-' after cd
    // you move to the prev path from old_pwd
    if (ft_strncmp(path, "-", 1) == 0)
    {
        oldpwd = my_getenv(env, "OLD_PWD");
        if (oldpwd != NULL)
        {
            ret = ft_move(env, oldpwd);
            free(oldpwd);
            return (ret);
        }
        return (0);
    }
    // if no return home, you return to given path
    return (ft_move(env, path));
}

// last part with $HOME and some path (after parse change the $HOME to direct path)