/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:47:03 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/04 16:50:02 by aheinane         ###   ########.fr       */
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

//void	creating_children( t_pipex *pipex, t_data *shell, int number_of_inputs)
void	creating_children( t_pipex *pipex, t_data *shell, int number_of_inputs)
{
	int		first_child = 0;
	(void)number_of_inputs;
	printf("!!!!!!!!!%d\n", shell->cmds->w_count);
	if(shell->cmds->w_count == 0)
	{
		first_child = 0;
		first_child = fork();
		if (first_child < 0)
			ft_error();
		if (first_child == 0)
			fun_first_child(shell, *pipex);
	}
	else if(shell->cmds->w_count == 1)
	{
		printf("Hello1\n");
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
	}
	
	else if(shell->cmds->w_count == 4)
	{
		printf("2222222\n");
		first_child = 0;
		//check_permissions(shell);
		//printf("???????%s\n", tokens->cmds[0].filenames[0]);
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