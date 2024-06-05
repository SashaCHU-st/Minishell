/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:59:21 by aheinane          #+#    #+#             */
/*   Updated: 2023/11/11 16:08:43 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lastlast;

	lastlast = *lst;
	if (!lastlast)
	{
		*lst = new;
		return ;
	}
	lastlast = ft_lstlast(lastlast);
	lastlast -> next = new;
}
