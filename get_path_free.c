/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Famahsha < famahsha@student.42abudhabi.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:02:35 by Famahsha          #+#    #+#             */
/*   Updated: 2023/10/13 14:02:45 by Famahsha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_and_print(char **path_bin)
{
	ft_putstr_fd("./minishell : ", 2);
	ft_putstr_fd(*path_bin, 2);
	ft_putstr_fd(" : command not found\n", 2);
	free(*path_bin);
	*path_bin = NULL;
	return (127);
}

int	free_and_print_denied(char **path_bin)
{
	ft_putstr_fd("./minishell : ", 2);
	ft_putstr_fd(*path_bin, 2);
	ft_putstr_fd(" : command not found\n", 2);
	free(*path_bin);
	*path_bin = NULL;
	return (127);
}
