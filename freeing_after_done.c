/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing_after_done.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:34:31 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/22 17:37:58 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void	freeing_at_end_shell_loop(t_data *sh)
{
	if (sh->pipe_tok)
	{
		printf("FROM PIPE TOK\n");
		free_array(sh->pipe_tok);
		sh->pipe_tok = NULL;
	}
	if (sh->cmds)
	{
		printf("HERE2\n");
		f_free_cmds(&sh->cmds, sh->cmds_count);
		sh->cmds = NULL;
	}
	if (sh->pid)
	{
		free(sh->pid);
		sh->pid = NULL;
	}
	if (sh->new_envp)
	{
		free_array(sh->new_envp);
		sh->new_envp = NULL;
	}
			if (sh->array)
	{
		printf("HERE\n");
		free_array(sh->array);
		//sh->array = NULL;
	}
}
