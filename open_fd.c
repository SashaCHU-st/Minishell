/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:46:25 by aheinane          #+#    #+#             */
/*   Updated: 2024/06/24 15:52:11 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void	check_permissions(t_built *data)
{
	if (data->inputs[2][0] == '\0' || data->inputs[3][0] == '\0')
	{
		write(2, "zsh: permission denied:\n", 24);
	}
	else if (data->inputs[2][0] == '\0' && data->inputs[3][0] == '\0')
	{
		write(2, "zsh: permission denied:\n", 24);
		exit(1);
	}
}

int	open_fd_in(t_pipex *pipex, t_built *data)
{
	if (access(data->inputs[0], F_OK | R_OK) == -1)
	{
		perror("No access for input");
		return (1);
	}
	pipex->fd_in = open(data->inputs[0], O_RDONLY);
	if (pipex->fd_in == -1)
	{
		perror("Error in infile");
		return (1);
	}
	return (0);
}

void	open_fd_out(t_pipex *pipex, t_built *data, int number_of_inputs)
{
	pipex->fd_out = open(data->inputs[number_of_inputs -1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->fd_out == -1)
	{
		perror("Error in outfile");
		close(pipex->fd_in);
		exit(EXIT_FAILURE);
	}
}
