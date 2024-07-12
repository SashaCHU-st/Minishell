/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 10:08:33 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/12 14:57:46 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void	check_permissions(t_data *shell)
{
	int	i;

	i = 0;
	if (!shell || !shell->cmds || !shell->cmds->filenames || !shell->cmds->filetype)
        error_message(shell, "Invalid shell or command structure", 1);
	while (shell->cmds->filenames[i])
	{
		if (access(shell->cmds->filenames[i], F_OK) != 0)
			error_message(shell, "zsh: no file path", 1);
		if (shell->cmds->filetype[i] == IN || shell->cmds->filetype[i] == HERE)
		{
			if (access(shell->cmds->filenames[i], R_OK) != 0)
				error_message(shell, "zsh: file is not readable", 1);
		}
		else if (shell->cmds->filetype[i] == OUT || shell->cmds->filetype[i] == APPEND)
		{
			if (access(shell->cmds->filenames[i], W_OK) != 0)
				error_message(shell, "zsh: file is not writable", 1);
		}
		i++;
	}
	// if (shell->cmds->filenames[2][0] == '\0' || shell->cmds->filenames[3][0] == '\0')
	// {
	// 	write(2, "zsh: permission denied:\n", 24);
	// }
	// else if (shell->cmds->word_tok[2][0] == '\0' && shell->cmds->word_tok[3][0] == '\0')
	// {
	// 	write(2, "zsh: permission denied:\n", 24);
	// 	exit(1);
	// }
}

void	child(t_pipex pipex, t_data *shell, int k)
{
	char	*final = NULL;
	int	i;

	if (k != 0)
		dup2(shell->pipe[k - 1][0], STDIN_FILENO);
	if (k != shell->cmds_count - 1)
		dup2(shell->pipe[k][1], STDOUT_FILENO);
	i = 0;
	while (i < (shell->pipe_count))
	{
	//	if (i != k)
		close(shell->pipe[i][0]);
	//	if (i != k - 1)
		close(shell->pipe[i][1]);
		i++;
	}
	check_permissions(shell);
	check_filetype(&pipex,&shell->cmds[k]);
	if(shell->cmds[k].word_tok[0][0] == '/')
		final = &shell->cmds[k].word_tok[0][0];
	else
		final = path_for_commands(&pipex, &shell->cmds[k].word_tok[0]);
	if (!final)
	{
		free(pipex.com_sec_child);
		free(final);
		exit(1);
	}
	if (execve(final, shell->cmds[k].word_tok, shell->envp) == -1)
	{
		printf("first  chiled execve brocken\n");
		free_fun(&pipex);
		}
}
void checking_path (t_data *shell, t_pipex *pipex, int i )
{
	char	*path;
	path = mine_path(shell);
	if(!path)
		return ;
	pipex->commands_path = ft_split(path, ':');
	if (!pipex->commands_path)
	{
		free_fun(pipex);
		i++;
	}

}
void piping(t_data *shell)
{
	shell->pipe_count = shell->cmds_count - 1;
	shell->pipe = (int**)malloc(sizeof(int *)* (shell->pipe_count));
	if(!shell->pipe)
	{
		perror("Error in malloc");
		exit(1);
	}
	int j = 0;
	while (j < shell->pipe_count)
	{
		shell->pipe[j]=(int *)malloc(sizeof(int) *2);
		if(!shell->pipe[j])
		{
			perror("Error in malloc");
			exit(1);
		}
		pipe(shell->pipe[j]);
		j++;
	}
}
void forking(t_data *shell, t_pipex pipex)
{
	int k = 0;
	shell->pid = (int*)malloc(sizeof(int) * (shell->cmds_count));
	if(!shell->pid)
	{
		perror("Error in malloc");
		exit(1);
	}
	while (k < shell->cmds_count)
	{
		shell->pid[k] = fork();
		if (shell->pid[k] < 0)
		{
			// if (shell->pid[k] < 0)
			// {
			// 	while (k != 0)
			// 		waitpid(shell->pid[k], NULL, 0);
			// 	k--;
			// }
			exit(EXIT_FAILURE);
		}
		else if (shell->pid[k] == 0)
			child(pipex, shell, k);
		k++;
	}
}
 void closing(t_data *shell)
 {
		int	m;

		m = 0;
		while (m < (shell->cmds_count - 1))
		{
			close(shell->pipe[m][0]);
			close(shell->pipe[m][1]);
			m++;
		}
		int x;
		x = 0;
		while (x < shell->cmds_count)
		{
			waitpid(shell->pid[x], NULL, 0);
			x++;
		}
 }