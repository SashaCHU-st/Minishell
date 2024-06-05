/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:33:28 by aheinane          #+#    #+#             */
/*   Updated: 2023/11/13 15:06:38 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst1;
	t_list	*new;
	void	*c;

	if (!lst)
		return (NULL);
	lst1 = NULL;
	while (lst)
	{
		c = f(lst ->content);
		new = ft_lstnew(c);
		if (!new)
		{
			del(c);
			ft_lstclear(&lst1, del);
			return (NULL);
		}
		ft_lstadd_back(&lst1, new);
		lst = lst -> next;
	}
	return (lst1);
}
