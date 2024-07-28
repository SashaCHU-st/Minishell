/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 10:08:33 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/20 15:11:37 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void	checking_path(t_data *shell, t_pipex *pipex, int i)
{
	shell->path = mine_path(shell, i);
	if (!shell->path)
	{
		shell->exit_status = 127;
		return ;
	}
	pipex->commands_path = ft_split(shell->path, ':');
	if (!pipex->commands_path)
	{
		shell->exit_status = 1;
		free_fun(pipex);
	}
}

void	piping(t_data *shell)
{
	int	j;

	j = 0;
	shell->pipe_count = shell->cmds_count - 1;
	shell->pipe = (int **)malloc(sizeof(int *) * (shell->pipe_count));
	if (!shell->pipe)
	{
		perror("Error in malloc");
		shell->exit_status = 1;
		exit(1);
	}
	while (j < shell->pipe_count)
	{
		shell->pipe[j] = (int *)malloc(sizeof(int ) * 2);
		if (!shell->pipe[j])
		{
			perror("Error in malloc");
			shell->exit_status = 1;
			//free_array(shell->pipe);
			//free(shell->pipe);
			exit(1);
		}
		pipe(shell->pipe[j]);
		j++;
	}
	// if (shell->pipe) {
    //     for (int i = 0; i < shell->pipe_count; i++) {
    //         free(shell->pipe[i]);
    //     }
    // 	free(shell->pipe);
    // }
}

void	closing(t_data *shell)
{
	int	m;
	int	x;
	int	status;

	m = 0;
	x = 0;
	
	while (m < (shell->cmds_count - 1))
	{
		close(shell->pipe[m][0]);
		close(shell->pipe[m][1]);
		m++;
	}
	while (x < shell->cmds_count)
	{
		waitpid(shell->pid[x], &status, 0);
		shell->exit_status = status;
		x++;
	}
	if (shell->pipe) {
        for (int i = 0; i < shell->pipe_count; i++) {
            free(shell->pipe[i]);
			shell->pipe[i] = NULL;
        }
    	free(shell->pipe);
    }
	shell->pipe = NULL;
}

void	forking(t_data *shell, t_pipex pipex)
{
	int	k;

	k = 0;
	shell->pid = (int *)malloc(sizeof(int) * (shell->cmds_count));
	if (!shell->pid)
	{
		perror("Error in malloc");
		exit(1);
	}
	while (k < shell->cmds_count)
	{
		shell->pid[k] = fork();
		if (shell->pid[k] < 0)
		{
			shell->exit_status = 1;
			free(shell->pid);
			exit(EXIT_FAILURE);
		}
		else if (shell->pid[k] == 0)
			child(pipex, shell, k);
		k++;
	}
}
