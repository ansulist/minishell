/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansulist <ansulist@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 10:49:09 by ansulist          #+#    #+#             */
/*   Updated: 2023/10/14 00:55:08 by ansulist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_full_path(t_env *env)
{
	char	*path;
	char	**path_split;

	path = my_getenv(env, "PATH");
	if (path == NULL)
		return (NULL);
	path_split = ft_newsplit(path, ':');
	free(path);
	return (path_split);
}

int	get_path_bin(t_env *env, char *cmd, char **path_bin)
{
	char	**paths;
	int		ret;

	*path_bin = NULL;
	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == 0)
		{
			*path_bin = ft_strdup(cmd);
			if (*path_bin == NULL)
				return (-1);
			return (0);
		}
		printf("./minishell : %s : permission denied\n", cmd);
		*path_bin = NULL;
		return (126);
	}
	paths = get_full_path(env);
	if (paths == NULL)
		return (free_and_print(path_bin));
	ret = get_path_bin_all(paths, cmd, path_bin);
	ft_free_twod_array(paths);
	return (ret);
}

void	print_2d_array(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		printf("%s\n", str[i]);
		i++;
	}
}

char	**evecve_prepare(char *path_bin, char **args, int nb_args)
{
	char	**execve_args;
	int		i;

	execve_args = malloc(sizeof(char **) * (nb_args + 2));
	if (execve_args == NULL)
		return (NULL);
	execve_args[0] = path_bin;
	i = 0;
	while (i < nb_args)
	{
		execve_args[i + 1] = args[i];
		i++;
	}
	execve_args[i + 1] = NULL;
	return (execve_args);
}

void	binary_command(t_env *env, char *cmd, char **args, int nb_args)
{
	int		ret;
	char	*path_bin;
	char	**envp;
	char	**execve_args;

	ret = get_path_bin(env, cmd, &path_bin);
	if (path_bin == NULL)
	{
		env->result = ret;
		return ;
	}
	execve_args = evecve_prepare(path_bin, args, nb_args);
	if (execve_args == NULL)
		return (free(path_bin));
	envp = ft_list_to_array(env->vars);
	if (envp == NULL)
	{
		ft_free_twod_array(execve_args);
		return (free(path_bin));
	}
	if (execve(path_bin, execve_args, envp) == -1)
		perror("error");
	ft_free_twod_array(envp);
	ft_free_twod_array(execve_args);
}
