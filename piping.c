/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 10:08:33 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/14 19:23:56 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

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
	checking_path(shell, &pipex, i); 
	if(if_it_is_builtins(&shell->cmds[k]) == 1 && !shell->path)
	{
		dprintf(2,"Executing built-in command: %s\n", shell->cmds[k].word_tok[0]);
		//dprintf(2,"Executing built-in command: %c\n", shell->cmds[k].word_tok[0][1]);
		builtins(shell, &shell->cmds[k]);
		closing(shell);
		exit(0);
	}
	else
	{
		check_permissions(shell);
		check_filetype(&pipex,&shell->cmds[k]);
		if(shell->cmds[k].word_tok[0][0] == '/')
			final = &shell->cmds[k].word_tok[0][0];
		else
			final = path_for_commands(&pipex, &shell->cmds[k].word_tok[0]);
		if (!final)
		{
			printf("%s: command not found\n", shell->cmds[k].word_tok[0]);
			free(final);
			exit(1);
		}
		if (execve(final, shell->cmds[k].word_tok, shell->envp) == -1)
		{
			dprintf(2,"first  chiled execve brocken\n");
			free_fun(&pipex);
		}
	}	
}

void checking_path (t_data *shell, t_pipex *pipex, int i )
{
	//char	*path;
	shell->path = mine_path(shell, i);
	if(!shell->path)
	{
		return ;
	}
	pipex->commands_path = ft_split(shell->path, ':');
	if (!pipex->commands_path)
	{
		free_fun(pipex);
		//i++;
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
	//dprintf(2, "Hello2\n");
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
