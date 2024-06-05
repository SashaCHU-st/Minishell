/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:24:44 by aheinane          #+#    #+#             */
/*   Updated: 2023/11/13 15:21:35 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dest_length;
	size_t	src_length;

	i = 0;
	j = 0;
	if ((src == NULL || dst == NULL) && dstsize == 0)
		return (0);
	dest_length = ft_strlen(dst);
	src_length = ft_strlen(src);
	if (dstsize <= dest_length)
		return (dstsize + src_length);
	j = dest_length;
	while (src[i] != '\0' && j + 1 < dstsize)
	{
		dst[j] = src[i];
		j++;
		i++;
	}
	dst[j] = '\0';
	return (dest_length + src_length);
}
