/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:18:08 by epolkhov          #+#    #+#             */
/*   Updated: 2024/07/15 15:46:37 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	in_pipes(t_data *shell, char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|')
		{
			if (input[i + 1] == '|')
			{
				msg_status(shell, "Syntax error: multiple pipes", 2);
				return (1);
			}
			i++;
			while (check_space(input[i]))
				i++;
			if (input[i] == '|' || input[i] == '\0')
			{
				msg_status(shell, "Syntax error: no input \
				after unexpected token", 2);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	in_redir(t_data *shell, char *in)
{
	int	i;

	i = 0;
	while (in[i])
	{
		if (in[i] == '<' || in[i] == '>' || \
			(in[i] == '>' && in[i + 1] == '>') || \
			(in[i] == '<' && in[i + 1] == '<'))
		{
			if (in[i + 1] == '>' || in[i + 1] == '<')
				i += 2;
			else
				i++;
			while (check_space(in[i]))
				i++;
			if (in[i] == '|' || in[i] == '\0' || in[i] == '<' || in[i] == '>')
			{
				msg_status(shell, "Syntax error: no input after \
				unexpected token", 2);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

void	error_message(t_data *shell, char *msg, int status)
{
	if (shell)
		free_all(shell);
	perror(msg);
	shell->exit_status = status;
	exit (status);
}

void	msg_status(t_data *shell, char *msg, int status)
{
	ft_putendl_fd(msg, 2);
	shell->exit_status = status;
}
