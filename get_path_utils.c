/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansulist <ansulist@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:33:42 by Famahsha          #+#    #+#             */
/*   Updated: 2023/10/13 00:39:44 by ansulist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_free(char *s1, char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*appended;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	appended = malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!appended)
		return (NULL);
	i = 0;
	j = 0;
	while (j < len_s1)
		appended[i++] = s1[j++];
	j = 0;
	while (j < len_s2)
		appended[i++] = s2[j++];
	appended[i] = '\0';
	free(s1);
	return (appended);
}

int	check_access(char **path_bin)
{
	if (access(*path_bin, F_OK) == 0)
	{
		if (access(*path_bin, X_OK) == 0)
			return (0);
		return (free_and_print_denied(path_bin));
	}
	return (-1);
}

int	get_path_bin_one(char *path, char *cmd, char **path_bin)
{
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	*path_bin = join_free(tmp, cmd);
	if (*path_bin == NULL)
		return (-1);
	if (access(*path_bin, F_OK) == 0)
	{
		if (access(*path_bin, X_OK) == 0)
			return (0);
		return (free_and_print_denied(path_bin));
	}
	free(*path_bin);
	*path_bin = NULL;
	return (1);
}

int	get_path_bin_all(char **paths, char *cmd, char **path_bin)
{
	int	i;
	int	ret;

	i = 0;
	while (paths[i])
	{
		ret = get_path_bin_one(paths[i], cmd, path_bin);
		if (ret != 1)
			return (ret);
		i++;
	}
	ft_putstr_fd("./minishell : ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(" : command not found\n", 2);
	return (127);
}
