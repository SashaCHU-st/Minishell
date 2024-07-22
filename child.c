/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:22:11 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/22 21:53:42 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void	dup_close(int k, t_data *shell)
{
	int	i;

	i = 0;
	if (k != 0)
		dup2(shell->pipe[k - 1][0], STDIN_FILENO);
	if (k != shell->cmds_count - 1)
		dup2(shell->pipe[k][1], STDOUT_FILENO);
	while (i < (shell->pipe_count))
	{
		close(shell->pipe[i][0]);
		close(shell->pipe[i][1]);
		i++;
	}
}

int find_slash(t_cmd *cmd)
{
	int i = 0;
	while (cmd->word_tok[i] != NULL)
	{
		if (strchr(cmd->word_tok[i], '/') != NULL)
			return 1;
		i++;
	}
	return 0;
}

void remove_dots(char *str)
{
	if (!str) return;

	char *src = str, *dst = str;
	while (*src)
	{
		if (*src != '.')
		{
			*dst++ = *src;
		}
		src++;
	}
	*dst = '\0';
}
void	exeve_for_commands(t_data *shell, t_pipex pipex, char *final, int k)
{
	checking_path(shell, &pipex, k);
	if (find_slash(&shell->cmds[k]) == 1)
	{
		final = shell->cmds[k].word_tok[0];
		printf("here1\n");
	}
	else
	{
		printf("here2\n");
		final = path_commands(shell, &pipex, &shell->cmds[k].word_tok[0]);
	}
	if (!final)
	{
		printf("%s: command not found\n", shell->cmds[k].word_tok[0]);
		free(final);
		exit(127);
	}
	if (execve(final, shell->cmds[k].word_tok, shell->envp) == -1)
	{
		shell->exit_status = 127;
		free_fun(&pipex);
		if (shell->envp)
		{
			free_array(shell->envp);
			shell->envp = NULL;
		}
		if (shell->new_envp)
		{
			free_array(shell->new_envp);
			shell->new_envp = NULL;
		}
		exit(127);
	}
}

void	child(t_pipex pipex, t_data *shell, int k)
{
	char	*final;
	int		i;

printf("$$$$\n");
	final = NULL;
	i = 0;
	dup_close(k, shell);
	check_filetype(shell, &pipex, &shell->cmds[k]);
	if (if_it_is_builtins(&shell->cmds[k]) == 1)
	{
		builtins(shell, &shell->cmds[k], k);
		exit(0);
	}
	else
		exeve_for_commands(shell, pipex, final, k);
}