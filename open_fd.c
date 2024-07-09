/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:46:25 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/09 15:58:03 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"


void	check_filetype(t_pipex *pipex, t_cmd *cmd)
{
	int i = 0;

	while (i < cmd->number_of_redir)
	{
		if (cmd->filetype[i] == IN)
			open_fd_in(pipex, cmd->filetype[i], cmd->filenames[i]);
		else if (cmd->filetype[i] == OUT)
			open_fd_out(pipex, cmd->filetype[i], cmd->filenames[i]);
		
		i++;
	}
}

int	open_fd_in(t_pipex *pipex, int filetype, char *filename)
{
	if(filetype == 1)
	{
		if (access(filename, F_OK | R_OK) == -1)
		{
			perror("No access for input");
			return (1);
		}
		pipex->fd_in = open(filename, O_RDONLY);
		if (pipex->fd_in == -1)
		{
			perror("Error in infile");
			return (1);
		}
	}
	return (0);
}

void	open_fd_out(t_pipex *pipex, int filetype, char *filename)
{
	if(filetype == 2)
	{	
		pipex->fd_out = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (pipex->fd_out == -1)
		{
			perror("Error in outfile");
			close(pipex->fd_in);
			exit(EXIT_FAILURE);
		}
	}
}