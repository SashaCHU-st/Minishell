/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   running_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:17:08 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/24 00:13:09 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void	redir_built(t_data *shell, t_pipex *pipex, int i)
{
	if(shell->cmds[0].number_of_redir > 0 && if_it_is_builtins(&shell->cmds[0]) == 0)
	{
		while (shell->cmds->filetype[i])
		{
			if (shell->cmds->word_tok == NULL &&(shell->cmds->filetype[i] == HERE || 
				shell->cmds->filetype[i] == OUT || shell->cmds->filetype[i] == IN
				|| shell->cmds->filetype[i] == APPEND))
				check_filetype(shell, pipex, shell->cmds);
			else if (shell->cmds->word_tok != NULL && (shell->cmds->filetype[i] == HERE || 
				shell->cmds->filetype[i] == OUT || shell->cmds->filetype[i] == IN
				|| shell->cmds->filetype[i] == APPEND))
			{
				forking(shell, *pipex);
				closing(shell);
			}
			i++;
		}
	}
}

void	no_redir_no_built(t_data *shell, t_pipex *pipex)
{
	if (if_it_is_builtins(&shell->cmds[0]) == 0 && shell->cmds[0].number_of_redir == 0)
	{
		forking(shell, *pipex);
		closing(shell);
	}
}