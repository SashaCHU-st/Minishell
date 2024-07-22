/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:28:20 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/22 17:39:04 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void	if_not_buil_and_no_redir(t_data *shell, t_pipex *pipex, int i)
{
	if (shell->cmds->filetype[i] == 0
		&& if_it_is_builtins(&shell->cmds[0]) == 0)
	{
		printf("1\n");
		forking(shell, *pipex);
		closing(shell);
	}
}

void	if_redir_but_no_buil(t_data *sh, t_pipex *pipex, int i)
{
	if (sh->cmds->filetype[i] > 0)
	{
		while (sh->cmds->filetype[i]
			&& if_it_is_builtins(&sh->cmds[0]) == 0)
		{
			if (sh->cmds->word_tok == NULL && (sh->cmds->filetype[i] == HERE
					|| sh->cmds->filetype[i] == OUT
					|| sh->cmds->filetype[i] == IN
					|| sh->cmds->filetype[i] == APPEND))
				check_filetype(sh, pipex, sh->cmds);
			else if (sh->cmds->word_tok != NULL
				&& (sh->cmds->filetype[i] == HERE
					|| sh->cmds->filetype[i] == OUT
					|| sh->cmds->filetype[i] == IN
					|| sh->cmds->filetype[i] == APPEND))
			{
				forking(sh, *pipex);
				closing(sh);
			}
			i++;
		}
	}
			if (sh->array)
	{
		printf("HERE\n");
		free_array(sh->array);
		sh->array = NULL;
	}
}

void	if_only_built(t_data *shell, t_pipex *pipex, int i)
{
	if (shell->cmds->word_tok[0] != NULL )
	{
		if (if_it_is_builtins(&shell->cmds[0]) == 1)
		{
			if (shell->cmds->filetype == NULL)
				builtins(shell, &shell->cmds[0], 0);
			else if (shell->cmds->filetype[i] == NONE)
				builtins(shell, &shell->cmds[0], 0);
			if (shell->cmds[0].number_of_redir > 0)
				redirection_with_builtins(shell, pipex, i);
		}
	}
}
