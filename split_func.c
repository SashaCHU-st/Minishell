/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:25:40 by epolkhov          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/07/22 18:01:40 by aheinane         ###   ########.fr       */
=======
/*   Updated: 2024/07/17 17:37:10 by aheinane         ###   ########.fr       */
>>>>>>> 6500cdf27b4a8692550d7123ed1a313c48acb161
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

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

static char	**split_array(unsigned int nb, char c, char const *s, char **array)
{
	unsigned int	start;
	int				len;
	unsigned int	i;

	start = 0;
	i = 0;
	while (i < nb)
	{
		if (s[start] != c)
		{
			len = get_substring_length(s, start, c);
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

static char	**f_fill_array(char const *s, char c, unsigned int nb)
{
	char	**array;
	char	**new_array;

	array = allocate_array(nb);
	if (!array)
		return (NULL);
	shell->new_array = split_array(nb, c, s, shell->array);
	if (!shell->new_array)
	{
		free(shell->array);
		return (NULL);
	}
	return (new_array);
}

char	**do_split(char const *s, char c)
{
	unsigned int	n_of_substr;

	if (!s)
		return (NULL);
	n_of_substr = num_of_str(s, c);

	return (f_fill_array(s, c, n_of_substr));
}
