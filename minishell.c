/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:52:26 by epolkhov          #+#    #+#             */
/*   Updated: 2024/07/17 14:20:13 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	g_signal_status = 0;

char	*read_line(t_data *line)
{
	char	*input;

	(void)line;
	input = readline("sashel -$ ");
	if (!input)
	{
		printf("exit\n");
		exit (EXIT_SUCCESS);
	}
	add_history(input);
	printf("input: %s\n", input);
	return (input);
}

void	running_commands(t_data *shell, int i, t_pipex *pipex )
{
	if ((shell->cmds->filetype[i] == HERE || shell->cmds->filetype[i] == OUT
			|| shell->cmds->filetype[i] == IN
			|| shell->cmds->filetype[i] == APPEND)
		&& shell->cmds->word_tok[0] == NULL)
		return ;
	else if (shell->cmds_count == 1 && if_it_is_builtins(&shell->cmds[i]) == 1)
	{
		if (shell->cmds->filetype[i] == NONE)
			builtins(shell, &shell->cmds[i], i);
		if (shell->cmds[i].number_of_redir > 0)
			redirection_with_builtins(shell, pipex, i);
		i++;
	}
	else
	{
		piping(shell);
		forking(shell, *pipex);
		closing(shell);
	}
	return ;
}

void	shell_loop(t_data *sh)
{
	char	*l;
	t_pipex	pipex;
	while (1)
	{
		l = read_line(sh);
		if (empty_line(l))
		{
			sh->exit_status = 2;
			continue ;
		}
		if (in_pipes(sh, l) == 0 && in_redir(sh, l) == 0 && q_pipe(sh, l) == 0)
		{
			l = change_to_space(l);
			split_line(l, sh);
			if (g_signal_status)
			{
				free(l);
				sh->exit_status = 130;
				continue ;
			}
			sh->exit_status = 0;
			running_commands(sh, 0, &pipex);
			printf("exit status shell loop: %d\n", sh->exit_status);
		}
		free(l);
	}
}

static char	**copy_envp(t_data *shell, char *envp[])
{
	int		count;
	char	**new_envp;
	int		i;

	count = 0;
	i = 0;
	while (envp[count] != NULL)
		count++;
	new_envp = malloc((count + 1) * sizeof(char *));
	if (new_envp == NULL)
		error_message(shell, "Failed to allocate memory", 1);
	while (i < count)
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (new_envp[i] == NULL)
			error_message(shell, "Failed to duplicate string", 1);
		i++;
	}
	new_envp[count] = NULL;
	return (new_envp);
}

int	main(int argc, char **argv, char *envp[])
{
	t_data	data;

	init_t_data(&data);
	(void)argv;
	data.envp = copy_envp(&data, envp);
	if (!data.envp)
		error_message(&data, "Failed to copy environment", 1);
	if (argc < 2)
	{
		if (isatty(STDIN_FILENO))
		{
			get_signal(HANDLER);
			shell_loop(&data);
		}
		else
		{
			perror("Terminal is not in interactive mode");
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
