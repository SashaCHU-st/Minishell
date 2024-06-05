/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:48:04 by aheinane          #+#    #+#             */
/*   Updated: 2023/11/13 16:04:27 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	*c;
	size_t	max;

	max = (size_t)-1;
	if (count > 0 && max / count < size)
		return (NULL);
	c = (size_t *) malloc(count * size);
	if (c == 0)
		return (c);
	ft_bzero (c, count * size);
	return (c);
}
