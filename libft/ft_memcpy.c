/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 10:55:19 by aheinane          #+#    #+#             */
/*   Updated: 2023/11/13 15:10:09 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*de;
	const unsigned char	*so;
	size_t				i;

	de = dst;
	so = src;
	i = 0;
	if (de == 0 && so == 0)
		return (0);
	while (i < n)
	{
		de[i] = so[i];
		i++;
	}
	return (dst);
}
