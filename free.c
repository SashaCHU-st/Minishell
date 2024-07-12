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
			free(array[i]);
			array[i] = NULL;
			i++;
	}
	free (array);
	array = NULL;
}

// void	f_free_array(char **str)
// {
// 	char	**ptr;

// 	if (!str)
// 		return ;
// 	ptr = str;
// 	while (*ptr)
// 	{
// 		free(*ptr);
// 		*ptr = NULL;
// 		ptr++;
// 	}
// 	free(str);
// 	str = NULL;
// }


void	ft_error(void)
{
	perror("Error fork()");
	exit(1);
}

void	f_free_cmds(t_cmd *cmds, int cmds_count)
{
	int		i;

	i = 0;
	while (i < cmds_count)
	{
		if (cmds[i].word_tok != NULL)
		{
			free_array(cmds[i].word_tok);
			cmds[i].word_tok = NULL;
		}
		if (cmds[i].filetype != NULL)
		{
			free(cmds[i].filetype);
			cmds[i].filetype = NULL;
		}
		if (cmds[i].filenames != NULL)
		{
			free_array(cmds[i].filenames);
			cmds[i].filenames = NULL;
		}
		i++;
	}
	free(cmds);
	cmds = NULL;
}

void	free_t_data(t_data *shell)
{
	if (shell->pipe_tok)
	{
		free_array(shell->pipe_tok);
		shell->pipe_tok = NULL;
	}
	if (shell->input_copy)
	{
		free(shell->input_copy);
		shell->input_copy = NULL;
	}
	if (shell->envp)
	{
		free_array(shell->envp);
		shell->envp = NULL;
	}
	if (shell->new_envp)
	{
		free_array(shell->new_envp);
		shell->new_envp = NULL;
	}
}

void	free_all(t_data *shell)
{
	if (shell == NULL)
		return ;
	if (shell->cmds)
	{
		if (shell->cmds != NULL)
		{
			f_free_cmds(shell->cmds, shell->cmds_count);
			shell->cmds = NULL;
		}
	}
	free_t_data(shell);
	if (shell->hd_delimeter)
	{
		free (shell->hd_delimeter);
		shell->hd_delimeter = NULL;
	}
	if (shell->tempfile_hd)
	{
		free (shell->tempfile_hd);
		shell->tempfile_hd = NULL;
	}
	
}

void	exit_free(t_data *shell, int status)
{
	free_all(shell);
	
	get_signal(shell, DEFAULT);
	exit (status);
}
