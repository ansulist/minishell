/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anitasulistiyawati <anitasulistiyawati@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:29:01 by ansulist          #+#    #+#             */
/*   Updated: 2022/11/15 02:12:04 by anitasulist      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*newnode;

	newnode = (t_list *)malloc(sizeof(t_list));
	if (newnode == NULL)
		return (NULL);
	newnode->next = NULL;
	newnode->content = content;
	return (newnode);
}
// guna fungsi ini adalah untuk mengisi next dengan null
// dan mengisi konten dengan konten
// menggunakan malloc untuk mengalokasikan memori yg akan diisi
// dengan apa yang diminta