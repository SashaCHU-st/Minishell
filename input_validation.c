/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:18:08 by epolkhov          #+#    #+#             */
/*   Updated: 2024/06/26 10:42:18 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	input_validation_pipes(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|')
		{
			if (input[i + 1] == '|')
			{
				ft_putendl_fd("Syntax error: multiple pipes", 2);
				return (1);
			}
			i++;
			while (check_space(input[i]))
				i++;
			if (input[i] == '|' || input[i] == '\0')
			{
				ft_putendl_fd("Syntax error: no input after pipe", 2);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	input_validation_redir(char *input)
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
			if (input[i] == '|' || input[i] == '\0' || input[i] == '<' || input[i] == '>')
			{
				ft_putendl_fd("Syntax error: no input after redirection or unexpected token", 2);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

void	error_message(char *msg)
{
	//ft_putstr_fd("Error\n", 2);
	ft_putendl_fd(msg, 2);
	exit (EXIT_FAILURE);
}

