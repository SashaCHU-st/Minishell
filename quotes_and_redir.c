/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_and_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:57:12 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/22 16:01:58 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quotes_redir(char *line)
{
	int	i;
	int	in_single_quote;
	int	in_double_quote;

	i = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (line[i] == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if ((line[i] == '<' || line[i] == '>')
			&& (in_single_quote || in_double_quote))
			return (1);
		i++;
	}
	return (0);
}

void	if_pipe_tok(t_data *shell)
{
	if (shell->pipe_tok)
	{
		while (shell->pipe_tok[shell->cmds_count])
			shell->cmds_count++;
	}
}
