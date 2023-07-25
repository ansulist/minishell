/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anitasulistiyawati <anitasulistiyawati@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:28:53 by asulisti          #+#    #+#             */
/*   Updated: 2022/11/18 13:18:29 by anitasulist      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_atoi(const char *str)
{
	int	i;
	int	realnb;
	int	minusorplus;

	i = 0;
	realnb = 0;
	minusorplus = 1;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
	{
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minusorplus *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		realnb = (realnb * 10) + (str[i] - 48);
		i++;
	}
	return (minusorplus * realnb);
}

int	main (void)
{
	printf ("%d", atoi("-9223372036854775807"));
}