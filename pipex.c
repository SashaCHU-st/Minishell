/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:47:03 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/12 19:12:19 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

char	*path_for_commands(t_pipex *pipex, char **child_command)
{
	char	*command;
	char	*command_temp;
	char	**current_path;

	current_path = pipex->commands_path;
	while (*current_path)
	{
		command_temp = ft_strjoin(*current_path, "/");
		if (command_temp == 0)
			free_fun(pipex);
		///ft_putendl_fd("path_for_commands\n",2);
		//dprintf(2, "child: %s %p \n", *child_command, *child_command);
		command = ft_strjoin(command_temp, *child_command);
		free(command_temp);
		if (command == 0)
			free_fun(pipex);
		if (access(command, F_OK | X_OK) == 0)
			return (command);
		free(command);
		current_path++;
		//ft_putendl_fd("path_for_commands1111\n",2);
	}
	if (!current_path)
	{
		ft_putstr_fd(*child_command, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	return (NULL);
}

char *mine_path(t_data *shell, int i)
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
			ft_putstr_fd("bash: ",2);
			ft_putstr_fd(shell->cmds[i].word_tok[0],2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
		return (NULL) ;
	}
	return (*shell->envp + 5);
}
