/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asulisti <asulisti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 17:13:24 by asulisti          #+#    #+#             */
/*   Updated: 2021/12/29 16:43:37 by asulisti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_calcul(int nb, int fd)
{
	if (nb < 0)
	{
		if (nb == -2147483648)
		{
			write(fd, "-2147483648", 11);
			nb = 0;
		}
		else
		{
			ft_putchar_fd('-', fd);
			nb = nb * -1;
		}
	}
	if (nb != 0)
	{
		ft_calcul(nb / 10, fd);
		ft_putchar_fd(nb % 10 + '0', fd);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == 0)
	{
		ft_putchar_fd('0', fd);
	}
	else
	{
		ft_calcul(n, fd);
	}
}
/*
int main (void)
{
    int nbr = 123456;
    ft_putnbr_fd(nbr, 1);
    return(0);
}
*/
