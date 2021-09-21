/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 16:48:50 by rcollas           #+#    #+#             */
/*   Updated: 2021/05/25 18:33:17 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*t;
	t_list	*tmp;

	t = *lst;
	if (!lst || !del)
		return ;
	while (t)
	{
		tmp = t->next;
		ft_lstdelone(t, del);
		t = tmp;
	}
	*lst = NULL;
}
