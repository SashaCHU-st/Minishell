/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:47:03 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/22 21:38:26 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void	free_for_path(t_data *shell, t_pipex *pipex)
{
	shell->exit_status = 1;
	free_fun(pipex);
}

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
			free_for_path(shell, pipex);
		command = ft_strjoin(command_temp, *child);
		free(command_temp);
		if (command == 0)
			free_for_path(shell, pipex);
		if (access(command, F_OK | X_OK) == 0)
			return (command);
		free(command);
		current_path++;
	}
	// if (!current_path)
	// {
		ft_putstr_fd(*child, 2);
		ft_putstr_fd(": command not found\n", 2);
		shell->exit_status = 127;
	//}
	return (NULL);
}

char	*mine_path(t_data *shell, int i)
{
	char	**envp_copy;

	envp_copy = shell->envp;
	if (envp_copy == NULL)
	{
		ft_putstr_fd("Environment variables not found.\n", 2);
		return (NULL);
	}
	while (*envp_copy != NULL && ft_strncmp("PATH=", *envp_copy, 5) != 0)
		envp_copy++;
	if (*envp_copy == NULL)
	{
		if (shell->cmds[i].word_tok[0][0] != '/')
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(shell->cmds[i].word_tok[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			shell->exit_status = 127;
		}
		return (NULL);
	}
	return (*envp_copy + 5);
}
