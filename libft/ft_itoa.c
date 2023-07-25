/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anitasulistiyawati <anitasulistiyawati@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 13:55:50 by asulisti          #+#    #+#             */
/*   Updated: 2022/01/21 20:18:53 by anitasulist      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	ft_length_int(int n)
{
	int	i;

	i = 0;
	if (n == -2147483648)
		return (10);
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa_negative(int n)
{
	int		i;
	char	*newnumber;
	int		len;

	len = ft_length_int(n);
	newnumber = (char *)malloc(len + 2);
	if (newnumber == NULL)
		return (NULL);
	newnumber[0] = '-';
	newnumber[len + 1] = '\0';
	i = 0;
	while (i < len)
	{
		newnumber[len - i] = (n % 10) * -1 + '0';
		n /= 10;
		i++;
	}
	return (newnumber);
}

char	*ft_itoa_positive(int n)
{
	int		i;
	char	*newnumber;
	int		len;

	len = ft_length_int(n);
	newnumber = (char *)malloc(len + 1);
	if (newnumber == NULL)
		return (NULL);
	newnumber[len] = '\0';
	i = 0;
	while (i < len)
	{
		newnumber[len - 1 - i] = (n % 10) + '0';
		n /= 10;
		i++;
	}
	return (newnumber);
}

char	*ft_itoa(int n)
{
	if (n < 0)
		return (ft_itoa_negative(n));
	else
		return (ft_itoa_positive(n));
}
/*
int main    (void)
{
    printf ("%s\n", ft_itoa(-2147483648));
    printf ("%s\n", ft_itoa(2));
    printf ("%s\n", ft_itoa(4));
    printf ("%s\n", ft_itoa(10));
    printf ("%s\n", ft_itoa(145));
    printf ("%s\n", ft_itoa(-145));
}
*/
