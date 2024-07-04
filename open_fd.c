/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:46:25 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/04 16:35:51 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	open_fd_in(t_pipex *pipex, t_data *shell)
{
	int i  = 0;
	printf("hello3\n");
	//printf("KUKU %s\n",shell->data.cmds[i].filenames[1]);
	printf("KUKU %s\n",shell->cmds[i].filenames[0]);
	if (access(shell->cmds->filenames[1], F_OK | R_OK) == -1)
	{
		printf("hello88888\n");
		perror("No access for input");
		return (1);
	}
	printf("hello4\n");
	pipex->fd_in = open(shell->cmds->filenames[1], O_RDONLY);
	if (pipex->fd_in == -1)
	{
		perror("Error in infile");
		return (1);
	}
	return (0);
}

//void	open_fd_out(t_pipex *pipex, t_data *shell, int number_of_inputs)
void	open_fd_out(t_pipex *pipex, t_data *shell)
{
	pipex->fd_out = open(shell->cmds->filenames[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->fd_out == -1)
	{
		perror("Error in outfile");
		close(pipex->fd_in);
		exit(EXIT_FAILURE);
	}
}