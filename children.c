/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:45:12 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/09 16:38:57 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void	fun_first_child(t_data *shell, t_pipex pipex)
{
	char	*final = NULL;
	
	// if(shell->cmds_count==1)
	// {
		
	// 	if (dup2(pipex.fd_in, STDIN_FILENO) == -1)
	// 		dprintf(2, "dup2 \n");
	// 	close(pipex.fd_in);
	// 	if (dup2(pipex.fd_out, STDOUT_FILENO) == -1)
	// 		dprintf(2,  "dup2 2\n");
	// 	close(pipex.fd_out);
	// 	//close(pipex.fd_in);
	// }

		if (dup2(pipex.fd[1], STDOUT_FILENO) == -1)
			dprintf(2, "dup2 \n");
		close(pipex.fd[0]);
		close(pipex.fd[1]);
		if (dup2(pipex.fd_in, STDIN_FILENO) == -1)
			dprintf(2,  "dup2 2\n");
		//close(pipex.fd_in);

	//printf("shell->cmds[0].word_tok[0] %s\n", shell->cmds[0].word_tok[0]);
	final = path_for_commands(&pipex, &shell->cmds[0].word_tok[0]);
	if (!final)
	{
		free(pipex.com_sec_child);
		free(final);
		exit(1);
	}
	if (execve(final, shell->cmds[0].word_tok, shell->envp) == -1)
	{
		printf("first  chiled execve brocken\n");
		free_fun(&pipex);
		}
	//close(STDIN_FILENO);
}

void	fun_second_child(t_data *shell, t_pipex pipex)
{
	//printf("HELLO FROM SECOND CHILD");
	//ft_putendl_fd("HELLO FROM SECOND CHILD2",1);
	char	*final;

	close(pipex.fd_in);
	dup2(pipex.fd[0], STDIN_FILENO);
	close(pipex.fd[0]);
	close(pipex.fd[1]);
	dup2(pipex.fd_out, STDOUT_FILENO);
	//pipex.com_sec_child = ft_split(shell->cmds->word_tok[1], ' ');
	if (pipex.com_sec_child == 0)
	{
		close(pipex.fd[0]);
		close(pipex.fd[1]);
		free_fun(&pipex);
	}
	//ft_putendl_fd("2nd child: after ft_split",2);
	final = path_for_commands(&pipex, &shell->cmds[1].word_tok[0]);
//	ft_putendl_fd("2nd child: after path_for_commands",2);
	if (!final)
	{
		ft_putendl_fd("2nd child . final is brocken",2);
		free(pipex.com_sec_child);
		free(final);
		exit(1);
	}
	//ft_putendl_fd("2nd child:execve",2);
	//dprintf(2, "2nd child: %s %s\n", final,  shell->cmds[1].word_tok[0]);
	if (execve(final, shell->cmds[1].word_tok, shell->envp) == -1)
	{
		ft_putendl_fd("first  chiled execve brocken\n",2);
		free_fun(&pipex);
	}
}

void	close_and_wait(t_data *shell, t_pipex *pipex, int first_child)
{
	(void)shell;
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	// close(pipex->fd_out);
	// close(pipex->fd_in);
	//ft_putendl_fd("before first waitpid\n",2);
	//printf("%d",first_child);
	waitpid(first_child, NULL, 0);
	//ft_putendl_fd("after first waitpid\n",2);
	//printf("HELLO CLOSE AND WAIT\n");
	if(shell->cmds_count >= 2 )	
	{
		// close(pipex->fd[0]);
		// close(pipex->fd[1]);
		waitpid(pipex->second_child, NULL, 0);
	}
	//ft_putendl_fd("after second waitpid\n",2);
}