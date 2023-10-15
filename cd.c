/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansulist <ansulist@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 10:48:25 by ansulist          #+#    #+#             */
/*   Updated: 2023/10/12 22:50:35 by ansulist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tilde_path(t_env *env, char *path, char *home)
{
	int		ret;
	char	*replace;

	replace = ft_strreplace(path, "~", home);
	if (replace == NULL)
		return (-1);
	ret = ft_move(env, replace);
	free(replace);
	return (ret);
}

int	path_dotdot(t_env *env)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
		return (-1);
	ft_move(env, cut_path(path));
	free(path);
	return (0);
}

int	path_dash(t_env *env)
{
	char	*oldpwd;
	int		ret;

	oldpwd = my_getenv(env, "OLD_PWD");
	if (oldpwd == NULL)
		return (-1);
	ret = ft_move(env, oldpwd);
	free(oldpwd);
	return (ret);
}

int	path_dollarsign(t_env *env, char *path)
{
	char	*replace;
	int		ret;

	replace = save_env_var(env, path);
	if (replace == NULL)
		return (-1);
	ret = ft_move(env, replace);
	free(replace);
	return (ret);
}

int	ft_cd(t_env *env, char *path)
{
	char	*home;
	int		ret;

	if (path == NULL || ft_strlen(path) == 0 || ft_strchr(path, '~') != 0)
	{
		home = my_getenv(env, "HOME");
		if (home == NULL)
			return (0);
		if (path == NULL || ft_strlen(path) == 0)
			ret = ft_move(env, home);
		else
			ret = tilde_path(env, path, home);
		free(home);
		return (ret);
	}
	if (path[0] == '.' && path[1] == '.')
		return (path_dotdot(env));
	if (ft_strncmp(path, "-", 1) == 0)
		return (path_dash(env));
	if (ft_strncmp(path, "$", 1) == 0)
		return (path_dollarsign(env, path));
	return (ft_move(env, path));
}
