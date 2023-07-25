/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anitasulistiyawati <anitasulistiyawati@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:44:19 by ansulist          #+#    #+#             */
/*   Updated: 2022/11/14 23:57:15 by anitasulist      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_lstsize (t_list *lst)
{
    int size;  

    size = 0;
    while (lst != NULL)
    {
        lst = lst->next;
        size++;
    }
    return (size);
}
// fungsi ini berguna untuk menghitung size dari node dalam list
// caranya dengan akses sampe akhir dan kembalikan 