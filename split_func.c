/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:25:40 by epolkhov          #+#    #+#             */
/*   Updated: 2024/05/29 20:40:44 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned int	num_of_str(const char *s, char c)
{
	unsigned int	count;
	int				in_field;

	if (!s)
		return (0);
	count = 0;
	in_field = 0;
	while (*s)
	{
		if (*s == c)
		{
			if (in_field)
				in_field = 0;
		}
		else
		{
			if (!in_field)
			{
				in_field = 1;
				count++;
			}
		}
		s++;
	}
	return (count);
}

static void	f_free_array(char **r)
{
	char	**ptr;

	if (!r)
		return ;
	ptr = r;
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(r);
}

static char	**f_fill_array(char const *s, char c, unsigned int nb)
{
	char			**array;
	unsigned int	start;
	unsigned int	i;
	unsigned int	len;

	array = (char **)malloc((nb + 1) * sizeof(char *));
	if (!array || !s)
		return (NULL);
	start = 0;
	i = 0;
	while (i < nb)
	{
		if (s[start] != c)
		{
			len = 0;
			while (s[start + len] != c && s[start + len] != '\0')
				len++;
			array[i] = ft_substr(s, start, len);
			if (!array[i])
			{
				f_free_array(array);
				return (NULL);
			}
			i++;
			start += len;
		}
		else
			start++;
	}
	array[i] = NULL;
	return (array);
}

char	**do_split(char const *s, char c)
{
	unsigned int	n_of_substr;

	if (!s)
		return (NULL);
	n_of_substr = num_of_str(s, c);
	return (f_fill_array(s, c, n_of_substr));
}
