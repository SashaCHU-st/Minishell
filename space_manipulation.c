/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_manipulation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-26 10:32:30 by epolkhov          #+#    #+#             */
/*   Updated: 2024-06-26 10:32:30 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

bool	check_space(char ch)
{
	if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r' || \
		ch == '\f' || ch == '\v')
		return (true);
	return (false);
}

char	*change_to_space(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\t' || line[i] == '\v' || line[i] == '\r' || line[i] == '\f')
			line[i] = ' ';
		i++;
	}
	return (line);
}

void	change_space_to_31(char *p_token)
{
	int	i;

	i = 0;
	while (p_token[i])
	{
		if (p_token[i] == '\'' || p_token[i] == '\"')
			i = skip_quotes(p_token, i);
		if (p_token[i] == ' ')
			p_token[i] = 31;
		i++;
	}
}
