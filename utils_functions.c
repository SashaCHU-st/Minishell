/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:22:56 by epolkhov          #+#    #+#             */
/*   Updated: 2024/07/17 17:52:29 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

char	*ft_strndup(const char *str, size_t n)
{
	size_t	len;
	size_t	i;
	char	*dup;

	len = 0;
	i = 0;
	while (str[i] && len < n)
	{
		len++;
		i++;
	}
	dup = (char *)malloc(len + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

bool	empty_line(t_data *shell, char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (true);
	while (line[i])
	{
		if (!isspace(line[i]))
		{
			shell->exit_status = 2;
			return (false);
		}
		i++;
	}
	free(line);
	return (true);
}

unsigned int	num_of_str(const char *s, char c)
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
