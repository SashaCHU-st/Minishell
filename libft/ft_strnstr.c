/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 09:35:46 by aheinane          #+#    #+#             */
/*   Updated: 2023/11/13 15:35:52 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (*needle == '\0')
		return ((char *)haystack);
	if (len == 0 && (!needle || !haystack))
		return (NULL);
	i = 0;
	while (haystack[i] && i < len)
	{
		j = 0;
		while ((needle[j] && haystack[i + j])
			&& (needle[j] == haystack[i + j] && i + j < len))
			j++;
		if (!needle[j])
		{
			return ((char *)&haystack[i]);
		}
		if (!haystack[i + j] || i + j == len)
		{
			return (0);
		}
		i++;
	}
	return (0);
}
