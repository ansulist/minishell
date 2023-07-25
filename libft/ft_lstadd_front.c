/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anitasulistiyawati <anitasulistiyawati@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:06:55 by ansulist          #+#    #+#             */
/*   Updated: 2022/11/14 23:57:05 by anitasulist      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
    t_list  *temp;

    if (*lst == NULL)
    {
        *lst = new;
        return ;
    }
    temp = *lst;
    *lst = new;
    new->next = temp; 
}
// fungsi ini berguna untung ngisi konten ke baris pertama di lst
// caranya adalah dengan cara masukin kontent awal ke temporary
// terus isi yang pertama dengan yang baru
// lalu isi next dengan konten original dalam lst yang dulunya ada di pertama