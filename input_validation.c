/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:18:08 by epolkhov          #+#    #+#             */
/*   Updated: 2024/06/05 14:45:14 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	has_unclosed_quotes(char *line)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			count++;
		i++;
	}
	if (count % 2 == 0)
		return (false);
	return (true);
}

bool	check_space(char ch)
{
	if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r' || \
		ch == '\f' || ch == '\v')
		return (true);
	return (false);
}

void	input_validation_pipes(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|')
		{
			if (input[i + 1] == '|')
			{
				perror("Syntax error: double pipes");
				exit(1);
			}
			i++;
			while (check_space(input[i]))
				i++;
			if (input[i] == '|' || input[i] == '\0')
			{
				perror("Syntax error: no input after pipe");
				exit(1);
			}
		}
		i++;
	}
}

void	input_validation_redir(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '<' || input[i] == '>' || \
			(input[i] == '>' && input[i + 1] == '>') || \
			(input[i] == '<' && input[i + 1] == '<'))
		{
			if (input[i + 1] == '>' || input[i + 1] == '<')
				i += 2;
			else
				i++;
			while (check_space(input[i]))
				i++;
			if (input[i] == '|' || input[i] == '\0')
			{
				perror("Syntax error: no input after redirection");
				exit(1);
			}
		}
		i++;
	}
}
void	error_message(char *msg)
{
	//ft_putstr_fd("Error\n", 2);
	ft_putendl_fd(msg, 2);
	exit (EXIT_FAILURE);
}