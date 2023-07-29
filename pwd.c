/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansulist <ansulist@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 10:49:46 by ansulist          #+#    #+#             */
/*   Updated: 2023/07/11 10:49:47 by ansulist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int pwd()
{
    char *path;

    path = getcwd(NULL, 0);
    if (path == NULL) {
        return (-1);
    }
    ft_putstr_fd(path, 1);
    ft_putstr_fd("\n", 1);
    free(path);
    return (0);
}

/*int main()
{
    pwd();
}*/
