/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:52:26 by epolkhov          #+#    #+#             */
/*   Updated: 2024/07/23 17:46:01 by aheinane         ###   ########.fr       */
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
	return (input);
}

void	running_commands(t_data *shell, int i, t_pipex *pipex )
{
	if (shell->cmds_count == 1)
	{
	printf("count: %d\n", shell->cmds_count);
	printf("number of redir: %d\n", shell->cmds[0].number_of_redir);
	// dprintf(2,"filetype: %d\n", shell->cmds[0].filetype[0]);
	printf("builin: %d\n", if_it_is_builtins(&shell->cmds[0]));
		//esli odna commanda ls
		if (if_it_is_builtins(&shell->cmds[0]) == 0 && shell->cmds[0].number_of_redir == 0)
		{
			printf("1\n");
			forking(shell, *pipex);
			closing(shell);
		}
		//esli est reditect i commanda cat << ll or <1.txt >33.txt
		printf("wtok: %s \n", shell->cmds->word_tok[0]);
		printf("wtok: %s \n", shell->cmds->word_tok[1]);
		if(shell->cmds[0].number_of_redir > 0 && if_it_is_builtins(&shell->cmds[0]) == 0)
		{
			while (shell->cmds->filetype[i])
			{
			printf("2\n");
				if (shell->cmds->word_tok == NULL &&(shell->cmds->filetype[i] == HERE || 
					shell->cmds->filetype[i] == OUT || shell->cmds->filetype[i] == IN
					|| shell->cmds->filetype[i] == APPEND))
					check_filetype(shell, pipex, shell->cmds);
				else if (shell->cmds->word_tok != NULL && (shell->cmds->filetype[i] == HERE || 
					shell->cmds->filetype[i] == OUT || shell->cmds->filetype[i] == IN
					|| shell->cmds->filetype[i] == APPEND))
				{
					forking(shell, *pipex);
					closing(shell);
				}
				i++;
			}
		if (shell->pid)
			{
				printf("YYYY\n");
				free(shell->pid);
				shell->pid = NULL;
			}
		}
		//esli builtin i redirect echo hi >88.txt
		if ( if_it_is_builtins(&shell->cmds[0]) == 1)
		{
			printf("3\n");
			if(if_it_is_builtins(&shell->cmds[0]) == 1)
			{
				// if (shell->cmds->filetype == NULL)
				// 	builtins(shell, &shell->cmds[0], 0);
				// else if (shell->cmds->filetype[i] == NONE)
				// 	builtins(shell, &shell->cmds[0], 0);
				if (shell->cmds[0].number_of_redir == 0)
					builtins(shell, &shell->cmds[0], 0);
				if (shell->cmds[0].number_of_redir > 0)
					redirection_with_builtins(shell, pipex, i);

			}
			// if (shell->cmds->filetype[i] > 0)
			// {
			// 	printf("4\n");
			// 	while (shell->cmds->filetype[i])
			// 	{
			// 		if (shell->cmds->word_tok == NULL &&(shell->cmds->filetype[i] == HERE || 
			// 			shell->cmds->filetype[i] == OUT || shell->cmds->filetype[i] == IN
			// 			|| shell->cmds->filetype[i] == APPEND))
			// 			check_filetype(shell, pipex, shell->cmds);
			// 		else if (shell->cmds->word_tok != NULL && (shell->cmds->filetype[i] == HERE || 
			// 			shell->cmds->filetype[i] == OUT || shell->cmds->filetype[i] == IN
			// 			|| shell->cmds->filetype[i] == APPEND))
			// 		{
			// 			forking(shell, *pipex);
			// 			closing(shell);
			// 		}
			// 		i++;
			// 	}
			// }
		}
	}
	else if (shell->cmds_count >1)
	{
		piping(shell);
		forking(shell, *pipex);
		closing(shell);
	}
		if (shell->pid)
			{
				free(shell->pid);
				shell->pid = NULL;
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
			continue ;
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
		}
	// 	if (sh->cmds->word_tok)
	// {
	// 	for (int i = 0; i < sh->cmds->w_count; i++) {
	// 		if (sh->cmds->word_tok[i]) {
	// 			free(sh->cmds->word_tok[i]);
	// 		}
	// 	}
	// 	free(sh->cmds->word_tok);
	// }
	if (sh->cmds)
	{
		for (int i = 0; i < sh->cmds_count; i++) {
		f_free_cmds(&sh->cmds[i]);
    }
    free(sh->cmds);
	sh->cmds = NULL;
	}
	if (sh->pid)
		{
			free(sh->pid);
			sh->pid = NULL;
		}
	if (sh->new_envp)
		{
			free_array(sh->new_envp);
			sh->new_envp = NULL;
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
		{
			error_message(shell, "Failed to duplicate string", 1);
			while (i > 0)
				free(new_envp[--i]);
			return (NULL);
		}
		i++;
	}
	new_envp[count] = NULL;
	return (new_envp);
}

int	main(int argc, char **argv, char *envp[])
{
	t_data	data;

	init_t_data(&data);
	init_t_data2(&data);
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
