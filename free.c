/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:46:00 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/23 16:38:02 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void	free_fun(t_pipex *pipex)
{
	if (pipex->commands_path != NULL)
		free_array(pipex->commands_path);
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
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free (array);
}

void	f_free_array(char **str)
{
	char	**ptr;

	if (!str)
		return ;
	ptr = str;
	while (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
		ptr++;
	}
	free(str);
}

static void	free_wtok(t_cmd *cmd)
{
	int	i;

	if (cmd->word_tok)
	{
		i = 0;
		while (i < cmd->w_count)
		{
			if (cmd->word_tok[i])
				free(cmd->word_tok[i]);
			i++;
		}
		free(cmd->word_tok);
	}
}

void	f_free_cmds(t_cmd *cmd)
{
	int	i;

	free_wtok(cmd);
	if (cmd->filenames)
	{
		i = 0;
		while (i < cmd->number_of_redir)
		{
			if (cmd->filenames[i])
				free(cmd->filenames[i]);
			i++;
		}
		free(cmd->filenames);
	}
	if (cmd->filetype)
		free(cmd->filetype);
}
