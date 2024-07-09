/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:47:03 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/09 16:00:06 by aheinane         ###   ########.fr       */
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
// void	check_filetype(t_pipex *pipex, t_cmd *cmd)
// {
// 	int i = 0;

// 	while (i < cmd->number_of_redir)
// 	{
// 		if (cmd->filetype[i] == IN)
// 			open_fd_in(pipex, cmd->filetype[i], cmd->filenames[i]);
// 		if (cmd->filetype[i] == OUT)
// 			open_fd_out(pipex, cmd->filetype[i], cmd->filenames[i]);
// 		i++;
// 	}
// 	printf("LOOP ENDED\n");
// }

// int	open_fd_in(t_pipex *pipex, int filetype, char *filename)
// {
// 	if(filetype == 1)
// 	{
// 		if (access(filename, F_OK | R_OK) == -1)
// 		{
// 			perror("No access for input");
// 			return (1);
// 		}
// 		pipex->fd_in = open(filename, O_RDONLY);
// 		if (pipex->fd_in == -1)
// 		{
// 			perror("Error in infile");
// 			return (1);
// 		}
// 	}
	
// 	return (0);
// }

// //void	open_fd_out(t_pipex *pipex, t_data *shell, int number_of_inputs)
// void	open_fd_out(t_pipex *pipex, int filetype, char *filename)
// {
// 	if(filetype == 2)
// 	{
		
// 	pipex->fd_out = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (pipex->fd_out == -1)
// 	{
// 		perror("Error in outfile");
// 		close(pipex->fd_in);
// 		exit(EXIT_FAILURE);
// 	}
// 	}

// }
//void	creating_children( t_pipex *pipex, t_data *shell, int number_of_inputs)
void creating_children(t_pipex *pipex, t_data *shell)
{
	int first_child = 0;

	first_child = fork();
	if (first_child < 0)
		ft_error();
	if (first_child == 0)
	{
		check_filetype(pipex, &shell->cmds[0]);
		fun_first_child(shell, *pipex);
	}
		// pipex->second_child = fork();
		// if (pipex->second_child < 0)
		// {
		// 	ft_error();
		// }
		// if (pipex->second_child == 0)
		// {
		// 	check_filetype(pipex, &shell->cmds[1]);
		// 	fun_second_child(shell, *pipex);
		// }
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