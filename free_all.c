/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:44:20 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/23 17:39:30 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void	free_t_data(t_data *shell)
{
	if (!shell)
		return ;
	if (shell->pipe_tok)
	{
		free_array(shell->pipe_tok);
		shell->pipe_tok = NULL;
	}
	// 		if (shell->array)
	// {
	// 	//	printf("HERE1\n");
	// 	//free_array(shell->array);
	// 	//shell->array = NULL;
	// }
	if (shell->pipe) {
        for (int i = 0; i < shell->pipe_count; i++) {
            free(shell->pipe[i]);
        }
    	free(shell->pipe);
    }
	if (shell->input_copy)
	{
		free(shell->input_copy);
		shell->input_copy = NULL;
	}
	if (shell->path)
	{
		free(shell->path);
		shell->path = NULL;
	}
	if (shell->pid)
	{
		free(shell->pid);
		shell->pid = NULL;
	}
	if (shell->envp)
	{
		free_array(shell->envp);
		shell->envp = NULL;
	}
	if (shell->new_envp)
	{
		free_array(shell->new_envp);
		shell->new_envp = NULL;
	}
	
}

void free_pipes(t_data *shell, int count)
{
	for (int i = 0; i < count; i++)
	{
		if (shell->pipe[i])
		{
			free(shell->pipe[i]);
			shell->pipe[i] = NULL;
		}
	}
	free(shell->pipe);
	shell->pipe = NULL;
}
void	free_all(t_data *shell)
{
	if (shell == NULL)
		return ;
	if (shell->cmds)
	{
		for (int i = 0; i < shell->cmds_count; i++) {
		f_free_cmds(&shell->cmds[i]);
    }
    free(shell->cmds);
	shell->cmds = NULL;
	}
	free_t_data(shell);
	if (shell->hd_delimeter)
	{
		free (shell->hd_delimeter);
		shell->hd_delimeter = NULL;
	}
}

void	exit_free(t_data *shell, int status)
{
	if (shell)
		free_all(shell);
	exit (status);
}
