/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:44:20 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/22 17:33:16 by aheinane         ###   ########.fr       */
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
	if (shell->new_envp)
	{
		printf("her2");
		free_array(shell->new_envp);
		shell->new_envp = NULL;
	}
}

void	free_all_sh(t_data *shell)
{
	if (shell == NULL)
		return ;
	if (shell->cmds)
	{
		printf("HERE2\n");
		f_free_cmds(&shell->cmds, shell->cmds_count);
		shell->cmds = NULL;
	}
		if (shell->kuku)
	{
		printf("HERE7\n");
		free_array(shell->kuku);
		shell->kuku = NULL;
	}
	free_t_data(shell);
	if (shell->pid)
	{
		free(shell->pid);
		shell->pid = NULL;
	}
	if (shell->array)
	{
		printf("HERE\n");
		free_array(shell->array);
		shell->array = NULL;
	}
		if (shell->new_array)
	{
		printf("HERE\n");
		free_array(shell->array);
		shell->array = NULL;
	}
	if (shell->hd_delimeter)
	{
		free (shell->hd_delimeter);
		shell->hd_delimeter = NULL;
	}
}

void	exit_free(t_data *shell, int status)
{
	if (shell)
		free_all_sh(shell);
	exit (status);
}
