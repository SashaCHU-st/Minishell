/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:46:00 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/11 10:33:00 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void	free_fun(t_pipex *pipex)
{
	if (pipex->commands_path != NULL)
		free_array(pipex->commands_path);
	// if (pipex->com_fir_child != NULL)
	// 	free_array(pipex->com_fir_child);
	// if (pipex->com_sec_child != NULL)
	// 	free_array(pipex->com_sec_child);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	exit(1);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		if (array[i] != NULL)
		{
			free(array[i]);
			array[i] = NULL;
			i++;
		}
	}
}

void	ft_error(void)
{
	perror("Error fork()");
	exit(1);
}
