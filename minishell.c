/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:52:26 by epolkhov          #+#    #+#             */
/*   Updated: 2024/07/15 20:53:00 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"


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

void running_commands(t_data *shell, int i, t_pipex *pipex )
{
	if ((shell->cmds->filetype[i] == HERE || shell->cmds->filetype[i] == OUT || shell->cmds->filetype[i] == IN \
				|| shell->cmds->filetype[i] == APPEND) && shell->cmds->word_tok[0] == NULL)
		return ;
	else if ( shell->cmds_count == 1 && if_it_is_builtins(&shell->cmds[i]) == 1 )
	{
		printf("one_cmd\n");
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

void	shell_loop(t_data *shell)
{
	char	*line;
	t_pipex	pipex;
	int		i;

	while (1)
	{
		i = 0;
		line = read_line(shell);
		if (line[i] == '\0' || line[i] == ' ' || line[i] == '\t' )
		{
			free(line);
			continue ;
		}
		if (input_validation_pipes(shell, line) == 0 && input_validation_redir(shell, line) == 0 \
					&& check_input_quotes_pipe(shell,line) == 0)
		{
			line = change_to_space(line);
			split_line(line, shell);
			if (!check_permissions(shell))
				running_commands(shell, i, &pipex);
			free(shell->cmds);
		}
	free(line);
	}
}

char **copy_envp(char *envp[])
{
	int count = 0;
	while (envp[count] != NULL)
		count++;
	char **new_envp = malloc((count + 1) * sizeof(char *));
	if (new_envp == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	int i = 0;
	while ( i < count)
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (new_envp[i] == NULL)
		{
			free_array(new_envp);
			perror("strdup");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	new_envp[count] = NULL;
	return(new_envp);
}


int	main(int argc, char **argv, char *envp[])
{
	t_data data;

	init_t_data(&data);
	(void)argv;
	data.envp = copy_envp(envp);
	if(argc < 2)
	{
		if (isatty(STDIN_FILENO))
		{
			get_signal(&data, HANDLER);
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
