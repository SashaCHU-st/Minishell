/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:47:03 by aheinane          #+#    #+#             */
/*   Updated: 2024/06/26 11:15:13 by aheinane         ###   ########.fr       */
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
		command = ft_strjoin(command_temp, *child_command);
		free(command_temp);
		if (command == 0)
			free_fun(pipex);
		if (access(command, F_OK | X_OK) == 0)
			return (command);
		free(command);
		current_path++;
	}
	if (!current_path)
	{
		ft_putstr_fd(*child_command, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	return (NULL);
}

void	creating_children( t_pipex *pipex, t_built *data, int number_of_inputs)
{
	int		first_child;
	int		second_child;

	first_child = 0;
	second_child = 0;
	check_permissions(data);
	if (open_fd_in(pipex, data) == 1)
		ft_putstr_fd(": No such file or directory\n", 2);
	else
	{
		first_child = fork();
		if (first_child < 0)
			ft_error();
		if (first_child == 0)
			fun_first_child(data, *pipex);
	}
	open_fd_out(pipex, data, number_of_inputs);
	second_child = fork();
	if (second_child < 0)
		ft_error();
	if (second_child == 0)
		fun_second_child(data, *pipex);
	close_and_wait(pipex, first_child, second_child);
}

char	*mine_path(t_built *shell)
{
	int	i;

	if (shell->envp == NULL)
		return (0);
	i = 0;
	while (shell->envp[i] != NULL)
	{
		if (ft_strncmp("PATH=", shell->envp[i], 5) == 0)
			return (shell->envp[i] + 5);
		i++;
	}
	ft_putstr_fd(shell->data.cmds->word_tok[1], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	ft_putstr_fd(shell->data.cmds->word_tok[2], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	exit(0);
}