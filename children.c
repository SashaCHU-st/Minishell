/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:45:12 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/04 16:33:35 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void	fun_first_child(t_data *shell, t_pipex pipex)
{
	char	*final;

	if(shell->cmds->w_count == 1)
			pipex.com_fir_child = ft_split(shell->cmds->word_tok[0], ' ');
	if(shell->cmds->w_count >=2)
	{
		dup2(pipex.fd[1], STDOUT_FILENO);
		close(pipex.fd[0]);
		close(pipex.fd[1]);
		dup2(pipex.fd_in, STDIN_FILENO);
		pipex.com_fir_child = ft_split(shell->cmds->word_tok[1], ' ');
	}
	if (pipex.com_fir_child == 0)
	{
		close(pipex.fd[0]);
		close(pipex.fd[1]);
		free_fun(&pipex);
	}
	final = path_for_commands(&pipex, pipex.com_fir_child);
	if (!final)
	{
		free(pipex.com_sec_child);
		free(final);
		exit(1);
	}
	if (execve(final, pipex.com_fir_child, shell->envp) == -1)
		free_fun(&pipex);
}

void	fun_second_child(t_data *shell, t_pipex pipex)
{
	char	*final;

	dup2(pipex.fd[0], STDIN_FILENO);
	close(pipex.fd[0]);
	close(pipex.fd[1]);
	dup2(pipex.fd_out, STDOUT_FILENO);
	pipex.com_sec_child = ft_split(shell->cmds->word_tok[2], ' ');
	if (pipex.com_sec_child == 0)
	{
		close(pipex.fd[0]);
		close(pipex.fd[1]);
		free_fun(&pipex);
	}
	final = path_for_commands(&pipex, pipex.com_sec_child);
	if (!final)
	{
		free(pipex.com_sec_child);
		free(final);
		exit(1);
	}
	if (execve(final, pipex.com_sec_child, shell->envp) == -1)
		free_fun(&pipex);
}

void	close_and_wait(t_data *shell, t_pipex *pipex, int first_child)
{
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	waitpid(first_child, NULL, 0);
	if(shell->cmds->w_count == 4 )
		waitpid(pipex->second_child, NULL, 0);
}