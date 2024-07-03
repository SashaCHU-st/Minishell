/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:46:25 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/02 15:11:30 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	open_fd_in(t_pipex *pipex, t_built *shell)
{
		printf("hello3\n");
	if (access(shell->data.cmds->word_tok[0], F_OK | R_OK) == -1)
	{
		perror("No access for input");
		return (1);
	}
	pipex->fd_in = open(shell->data.cmds->word_tok[0], O_RDONLY);
	if (pipex->fd_in == -1)
	{
		perror("Error in infile");
		return (1);
	}
	return (0);
}

void	open_fd_out(t_pipex *pipex, t_built *shell, int number_of_inputs)
{
	pipex->fd_out = open(shell->data.cmds->word_tok[number_of_inputs -1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->fd_out == -1)
	{
		perror("Error in outfile");
		close(pipex->fd_in);
		exit(EXIT_FAILURE);
	}
}