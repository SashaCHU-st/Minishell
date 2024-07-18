/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 10:08:33 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/17 13:11:46 by aheinane         ###   ########.fr       */
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
        for (int i = 0; i < shell->pipe_count; i++)
            free(shell->pipe[i]);
    	free(shell->pipe);
		exit(1);
	}
	//dprintf(2, "pipes num %d\n", shell->pipe_count);
	while (j < shell->pipe_count)
	{
		shell->pipe[j] = (int *)malloc(sizeof(int ) * 2);
		if (!shell->pipe[j])
		{
			perror("Error in malloc");
			shell->exit_status = 1;
			//free_array(shell->pipe);
			
        	for (int i = 0; i < shell->pipe_count; i++)
            	free(shell->pipe[i]);
    		free(shell->pipe);
			exit(1);
		}
		pipe(shell->pipe[j]);
		j++;
	}
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
}
