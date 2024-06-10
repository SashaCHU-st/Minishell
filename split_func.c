/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:25:40 by epolkhov          #+#    #+#             */
/*   Updated: 2024/06/10 13:28:12 by epolkhov         ###   ########.fr       */
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

// static int	f_free_array(char **r)
// {
// 	char	**ptr;

// 	if (!r)
// 		return (1);
// 	ptr = r;
// 	while (*ptr)
// 	{
// 		free(*ptr);
// 		ptr++;
// 	}
// 	free(r);
// 	return (1);
// }

char	*f_free_array(char **str)
{
	char	**ptr;

	ptr = str;
	while (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
		ptr++;
	}
	free(ptr);
	return (NULL);
}

static unsigned int	get_substring_length(const char *s, \
			unsigned int start, char c)
{
	unsigned int	len;

	len = 0;
	while (s[start + len] != c && s[start + len] != '\0')
		len++;
	return (len);
}

static char	**allocate_array(unsigned int nb)
{
	char	**array;

	array = (char **)malloc((nb + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	return (array);
}

static char	**f_fill_array(char const *s, char c, unsigned int nb)
{
	char			**array;
	unsigned int	start;
	unsigned int	i;
	unsigned int	len;

	array = allocate_array(nb);
	start = 0;
	i = 0;
	while (i < nb)
	{
		if (s[start] != c)
		{
			len = get_substring_length(s, start, c);
			array[i] = ft_substr(s, start, len);
			if (!array[i])
				f_free_array(array);
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
