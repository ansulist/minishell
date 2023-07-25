/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anitasulistiyawati <anitasulistiyawati@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 22:34:26 by asulisti          #+#    #+#             */
/*   Updated: 2022/01/25 13:52:23 by anitasulist      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*pointer;

	pointer = (void *)malloc(count * size);
	if (pointer == NULL)
		return (NULL);
	ft_bzero(pointer, count * size);
	return (pointer);
}
/*
// calloc digunakan untuk mengalokasikan malloc dan 
// diisi sementara pake 0 biar nanti bisa di pakai
*/
