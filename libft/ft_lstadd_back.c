/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anitasulistiyawati <anitasulistiyawati@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 15:43:02 by ansulist          #+#    #+#             */
/*   Updated: 2022/11/14 23:57:07 by anitasulist      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    ft_lstadd_back(t_list **lst, t_list *new)
{
    t_list *last_list_element;

    if (new == NULL)
        return ;
    if (*lst == NULL)
    {
        *lst = new;
        return ;
    }
    last_list_element = ft_lstlast(*lst);
    last_list_element->next = new;
}
// guna fungsi ini adalah untuk menambahkan bode baru di akhir lst
// pertama kamu pergi ke pointer paling akhir pake ft_lstlast
// setelah ketemu, dia akan return NULL
// di baris akhir kamu mengganti NULL dengan yg baru
