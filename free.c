/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:46:00 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/02 15:11:14 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void	free_fun(t_pipex *pipex)
{
	if (pipex->commands_path != NULL)
		free_array(pipex->commands_path);
	if (pipex->com_fir_child != NULL)
		free_array(pipex->com_fir_child);
	if (pipex->com_sec_child != NULL)
		free_array(pipex->com_sec_child);
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
	free (array);
	array = NULL;
}

void	ft_error(void)
{
	perror("Error fork()");
	exit(1);
}

void	f_free_cmds(t_cmd *cmds, int cmds_count)
{
	int		i;
	int		j;

	i = 0;
	while (i < cmds_count)
	{
		j = 0;
		while (j < cmds->w_count)
		{
			free(cmds->word_tok[j]);
			cmds->word_tok[j] = NULL;
			j++;
		}
		free(cmds->word_tok);
		cmds->word_tok = NULL;
		i++;
	}
	free(cmds);
	cmds = NULL;
}

void	free_all(t_data *shell)
{
	if (shell->cmds)
		f_free_cmds(shell->cmds, shell->cmds_count);
	if (shell->cmds->filetype)
		free(shell->cmds->filetype);
	if (shell->cmds->filenames)
		free_array(shell->cmds->filenames);
	if (shell->pipe_tok)
		free_array(shell->pipe_tok);
	if (shell->input_copy)
		free(shell->input_copy);
	if (shell->hd_delimeter)
		free (shell->hd_delimeter);
	if (shell->tempfile_hd)
		free (shell->tempfile_hd);
}

void	exit_free(t_data *shell, int status)
{
	free_all(shell);
	free_array(shell->envp);
	free_array(shell->new_envp);
	get_signal(DEFAULT);
	exit (status);
}
