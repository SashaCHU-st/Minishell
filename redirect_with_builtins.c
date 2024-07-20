/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_with_builtins.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:48:00 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/17 13:54:48 by aheinane         ###   ########.fr       */
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

void	redirection_out_builtin(t_data *shel, t_pipex *pipex, int i)
{
	//printf("dididid\n");
	shel->parent_out = dup(STDOUT_FILENO);
	//printf("daaaaaaa\n");
	open_fd_out(shel, pipex, shel->cmds->filetype[i], *shel->cmds->filenames);
	//check_filetype(shel, pipex, &shel->cmds[i]);
	//printf("nuuuuut\n");
	builtins(shel, &shel->cmds[i], i);
	if (dup2(shel->parent_out, STDOUT_FILENO) < 0)
		printf("dup2 \n");
	//printf("come on\n");
	close(shel->parent_out);
}

void	redirection_with_builtins(t_data *shell, t_pipex *pipex, int i)
{
	//printf("dididid\n");
	if (shell->cmds->filetype[i] == OUT)
	{
		//printf("LLLLLL\n");
		redirection_out_builtin(shell, pipex, i);
		//printf("wwwwwwwwwwww\n");
	}
	if (shell->cmds->filetype[i] == IN)
		redirection_in_builtin(shell, pipex, i);
}
