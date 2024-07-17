/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:46:25 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/15 16:36:28 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void	check_filetype(t_data *shell, t_pipex *pipex, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->number_of_redir)
	{
		if (cmd->filetype[i] == IN || cmd->filetype[i] == HERE)
			open_fd_in(shell, pipex, cmd->filetype[i], cmd->filenames[i]);
		if (cmd->filetype[i] == OUT)
			open_fd_out(shell, pipex, cmd->filetype[i], cmd->filenames[i]);
		if (cmd->filetype[i] == APPEND)
			open_fd_out(shell, pipex, cmd->filetype[i], cmd->filenames[i]);
		i++;
	}
}

int	open_fd_in(t_data *shell, t_pipex *pipex, int filetype, char *filename)
{
	if (filetype == IN || filetype == HERE)
	{
		if (access(filename, F_OK | R_OK) == -1)
		{
			//perror("No access for input");
			//shell->exit_status = 1;
			write_msg_status(shell, "sashel: permission denied: file is not readable", 1);
			exit (1);//return (1);
		}
		pipex->fd_in = open(filename, O_RDONLY);
		if (pipex->fd_in == -1)
		{
			//perror("Error in infile");
			//shell->exit_status = 1;
			write_msg_status(shell, "sashel: permission denied: file is not readable", 1);
			exit(1);//return (1);
		}
		if (dup2(pipex->fd_in, STDIN_FILENO) < 0)
			printf("dup2 \n");
		close(pipex->fd_in);
	}
	return (0);
}

void	open_fd_out(t_data *shell, t_pipex *pipex, int filetype, char *filename)
{
	if (filetype == OUT)
	{
		pipex->fd_out = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (pipex->fd_out == -1)
		{
			close(pipex->fd_in);
			//shell->exit_status = 1;
			write_msg_status(shell, "sashel: permission denied: file is not writable", 1);
			exit(1);
		}
		if (dup2(pipex->fd_out, STDOUT_FILENO) < 0)
			printf("dup2 \n");
		close(pipex->fd_out);
	}
	else if (filetype == APPEND)
	{
		pipex->fd_out = open(filename, O_CREAT | O_APPEND | O_RDWR, 0644);
		if (pipex->fd_out == -1)
		{
			//shell->exit_status = 1;
			close(pipex->fd_in);
			write_msg_status(shell, "sashel: permission denied: file is not writable", 1);
			exit(1);
		}
		if (dup2(pipex->fd_out, STDOUT_FILENO) < 0)
			printf("dup2 \n");
		close(pipex->fd_out);
	}
}
