/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_with_builtins.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:48:00 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/16 19:54:55 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void	redirection_in_builtin(t_data *shell, t_pipex *pipex, int i)
{
	shell->parent_in = dup(STDIN_FILENO);
	check_filetype(shell, pipex, &shell->cmds[i]);
	if (dup2(shell->parent_in, STDIN_FILENO) < 0)
		printf("dup2 \n");
	close(shell->parent_out);
}

void	redirection_out_builtin(t_data *shell, t_pipex *pipex, int i)
{
	shell->parent_out = dup(STDOUT_FILENO);
	open_fd_out(shell, pipex, shell->cmds->filetype[i], *shell->cmds->filenames);
	check_filetype(shell, pipex, &shell->cmds[i]);
	builtins(shell, &shell->cmds[i], i);
	if (dup2(shell->parent_out, STDOUT_FILENO) < 0)
		printf("dup2 \n");
	close(shell->parent_out);
}

void	redirection_with_builtins(t_data *shell, t_pipex *pipex, int i)
{
	if (shell->cmds->filetype[i] == OUT)
		redirection_out_builtin(shell, pipex, i);
	if (shell->cmds->filetype[i] == IN)
		redirection_in_builtin(shell, pipex, i);
}
