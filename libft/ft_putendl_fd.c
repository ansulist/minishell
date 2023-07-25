/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anitasulistiyawati <anitasulistiyawati@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 17:13:13 by asulisti          #+#    #+#             */
/*   Updated: 2022/11/18 12:24:23 by anitasulist      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
    if (s == NULL)
        return ;
	write(fd, s, ft_strlen(s));
	ft_putchar_fd('\n', fd);
}
/*
int main () 
{
    char test[] = "I went crazy over you";
    ft_putendl_fd(test, 1);
    return(0);
}
*/
