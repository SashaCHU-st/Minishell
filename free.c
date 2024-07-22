/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:46:00 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/22 17:25:16 by aheinane         ###   ########.fr       */
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

void	ft_error(void)
{
	perror("Error fork()");
	exit(1);
}

void f_free_cmds(t_cmd **cmds, int cmds_count)
{
    int i;

    if (cmds == NULL || *cmds == NULL)
        return;

    i = 0;
    while (i < cmds_count)
    {
        if ((*cmds)[i].word_tok != NULL)
        {
            free_array((*cmds)[i].word_tok);
            (*cmds)[i].word_tok = NULL;
        }
        if ((*cmds)[i].filetype != NULL)
        {
            free((*cmds)[i].filetype);
            (*cmds)[i].filetype = NULL;
        }
        if ((*cmds)[i].filenames != NULL)
        {
            free_array((*cmds)[i].filenames);
            (*cmds)[i].filenames = NULL;
        }
        i++;
    }
    free(*cmds);
    *cmds = NULL;  // Nullify the original pointer
}

