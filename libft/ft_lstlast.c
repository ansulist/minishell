/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anitasulistiyawati <anitasulistiyawati@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:56:07 by ansulist          #+#    #+#             */
/*   Updated: 2022/11/14 23:57:11 by anitasulist      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list  *ft_lstlast(t_list *lst)
{
    if (lst == NULL)
        return (NULL);
    while (lst != NULL)
    {
        if (lst->next == NULL)
            return (lst);
        lst = lst->next;
    }
    return (lst);
}
// fungsi ini berguna buat ngasih kamu pointer ke
// list terakhir yang ada di lst
// caranya, kamu loop sampai ke akhir 
// kalo udah sampe terakhir, kamu balikin itu alamat