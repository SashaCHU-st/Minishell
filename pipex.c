/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:47:03 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/08 17:12:19 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

char	*path_for_commands(t_pipex *pipex, char **child_command)
{
	char	*command;
	char	*command_temp;
	char	**current_path;

	printf("Hello5");
	current_path = pipex->commands_path;
	while (*current_path)
	{
		command_temp = ft_strjoin(*current_path, "/");
		if (command_temp == 0)
			free_fun(pipex);
		ft_putendl_fd("path_for_commands\n",2);
		dprintf(2, "child: %s %p \n", *child_command, *child_command);
		command = ft_strjoin(command_temp, *child_command);
		free(command_temp);
		if (command == 0)
			free_fun(pipex);
		if (access(command, F_OK | X_OK) == 0)
			return (command);
		free(command);
		current_path++;
		ft_putendl_fd("path_for_commands1111\n",2);
	}
	if (!current_path)
	{
		ft_putstr_fd(*child_command, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	return (NULL);
}

//void	creating_children( t_pipex *pipex, t_data *shell, int number_of_inputs)
void	creating_children( t_pipex *pipex, t_data *shell)
{
	int		first_child = 0;

	if(shell->cmds_count == 1)
	{
		printf("Hello1\n");
		first_child = 0;
		//check_permissions(shell);
		if (open_fd_in(pipex, shell) == 1)
			ft_putstr_fd(": No such file or directory\n", 2);
		else
		{
			printf("Hello2\n");
			first_child = fork();
			printf("Hello3\n");
			if (first_child < 0)
				ft_error();
			if (first_child == 0)
				fun_first_child(shell, *pipex);
		}
	}
	
	if(shell->cmds_count == 2)
	{
		first_child = 0;
		//check_permissions(shell);
		if (open_fd_in(pipex, shell) == 1)
			ft_putstr_fd(": No such file or directory\n", 2);
		else
		{
			first_child = fork();
			if (first_child < 0)
				ft_error();
			if (first_child == 0)
				fun_first_child(shell, *pipex);
		}
		open_fd_out(pipex, shell);
		pipex->second_child=0;
		pipex->second_child = fork();
		if (pipex->second_child  < 0)
			ft_error();
		if (pipex->second_child == 0)
			fun_second_child(shell, *pipex);
	}
	close_and_wait(shell, pipex, first_child);
}


char	*mine_path(t_data *shell)
{
	//int	i;

	if (shell->envp == NULL)
		return (0);
	while (ft_strncmp("PATH=", *shell->envp, 5) != 0)
	{
		shell->envp++;
		if (*shell->envp == NULL)
		{
			ft_putstr_fd(shell->cmds->word_tok[1], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			ft_putstr_fd(shell->cmds->word_tok[2], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			exit(0);
		}
	}
	return (*shell->envp + 5);
}