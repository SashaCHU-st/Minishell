/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:47:03 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/16 20:09:13 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

char	*path_commands(t_data *shell, t_pipex *pipex, char **child)
{
	char	*command;
	char	*command_temp;
	char	**current_path;

	current_path = pipex->commands_path;
	while (*current_path)
	{
		command_temp = ft_strjoin(*current_path, "/");
		if (command_temp == 0)
		{
			shell->exit_status = 1;
			free_fun(pipex);
		}
		command = ft_strjoin(command_temp, *child);
		free(command_temp);
		if (command == 0)
		{
			shell->exit_status = 1;
			free_fun(pipex);
		}
		if (access(command, F_OK | X_OK) == 0)
			return (command);
		free(command);
		current_path++;
	}
	if (!current_path)
	{
		ft_putstr_fd(*child, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	return (NULL);
}

char	*mine_path(t_data *shell, int i)
{
	if (shell->envp == NULL)
	{
		ft_putstr_fd("Environment variables not found.\n", 2);
		return (NULL);
	}
	while (*shell->envp != NULL && ft_strncmp("PATH=", *shell->envp, 5) != 0)
		shell->envp++;
	if (*shell->envp == NULL)
	{
		if (i < shell->cmds_count && shell->cmds[i].word_tok[0][0] != '/')
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(shell->cmds[i].word_tok[0], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			shell->exit_status = 127;
		}
		return (NULL);
	}
	return (*shell->envp + 5);
}
