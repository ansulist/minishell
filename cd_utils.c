/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansulist <ansulist@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:05:21 by Famahsha          #+#    #+#             */
/*   Updated: 2023/10/12 22:52:36 by ansulist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*my_getenv(t_env *env, char *key)
{
	t_list	*temp;

	temp = env->vars;
	while (temp != NULL)
	{
		if (ft_strncmp(key, (char *)temp->content, ft_strlen(key)) == 0
			&& ((char *)temp->content)[ft_strlen(key)] == '=')
			return (ft_strdup(temp->content + ft_strlen(key) + 1));
		temp = temp->next;
	}
	return (NULL);
}

char	*cut_path(char *str)
{
	int		len;
	char	*ret;

	len = ft_strlen(str) - 1;
	while (str[len] != '/' && len > 0)
		len--;
	ret = ft_strndup(str, len);
	return (ret);
}

int	ft_chdir(char *path)
{
	if (chdir(path) < 0)
	{
		perror(path);
		return (-1);
	}
	return (0);
}

int	ft_move(t_env *env, char *path)
{
	char	*pwd;
	char	*new_path;
	int		ret;

	if (path == NULL)
		return (0);
	if (ft_chdir(path) == -1)
		return (0);
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

char	*save_env_var(t_env *env, char *key)
{
	t_list	*var;
	char	*path;

	var = ft_lstfind(env->vars, &cmp_var, key);
	if (var == NULL)
		return (NULL);
	path = ft_strdup((char *)(var->content) + ft_strlen(key) + 1);
	return (path);
}
