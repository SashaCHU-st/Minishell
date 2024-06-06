/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:27:32 by epolkhov          #+#    #+#             */
/*   Updated: 2023/11/15 13:17:36 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 *  The strdup() function allocates sufficient memory for a copy of the
     string s1, does the copy, and returns a pointer to it. 
 * if insufficient memory is available, NULL is returned.
 */

char	*ft_strdup(const char *src)
{
	int		len;
	int		i;
	char	*newstr;

	len = ft_strlen(src);
	i = 0;
	newstr = ((char *)malloc(sizeof(char) * (len + 1)));
	if (newstr == 0)
		return (0);
	while (src[i])
	{
		newstr[i] = src[i];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}
