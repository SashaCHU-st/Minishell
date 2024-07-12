/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:52:26 by epolkhov          #+#    #+#             */
/*   Updated: 2024/07/12 19:00:24 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
 int if_it_is_builtins( t_cmd *cmd)
{
	if (ft_strncmp(cmd->word_tok[0], "pwd", 4) == 0)
			return(1);
	else if (ft_strncmp(cmd->word_tok[0], "echo", 5) == 0)
			return(1);
	else if (ft_strncmp(cmd->word_tok[0], "env", 4) == 0)
			return(1);
	else if (ft_strncmp(cmd->word_tok[0], "export", 7) == 0)
			return(1);
	else if (ft_strncmp(cmd->word_tok[0], "cd", 3) == 0)
			return(1);
	else if (ft_strncmp(cmd->word_tok[0], "unset", 6) == 0)
			return(1);
	else
		return(0);
	return(1);
}
//void builtins(t_data *data, t_cmd *cmd)
int builtins(t_data *data, t_cmd *cmd)
{
	if (ft_strncmp(cmd->word_tok[0], "pwd", 4) == 0)
			ft_pwd();
	else if (ft_strncmp(cmd->word_tok[0], "echo", 5) == 0)
			ft_echo(data, cmd->w_count);
	else if (ft_strncmp(cmd->word_tok[0], "env", 4) == 0)
		ft_env(data);
	else if (ft_strncmp(cmd->word_tok[0], "export", 7) == 0)
		ft_export(data, cmd->w_count);
	else if (ft_strncmp(cmd->word_tok[0], "cd", 3) == 0)
		ft_cd(data, cmd->w_count);
	else if (ft_strncmp(cmd->word_tok[0], "unset", 6) == 0)
			ft_unset(data, cmd->w_count);
	else
		return(0);
	return(1);
}

char	*read_line(t_data *line)
{
	char	*input;

	(void)line;
	input = readline("your 🐰 wrote -$ ");
	if (!input)
	{
		printf("exit\n");
		exit (EXIT_SUCCESS);
	}
	add_history(input);
	printf("input: %s\n", input);
	return (input);
}

void shell_loop(t_data *shell)
{
	char	*line;
	t_pipex	pipex;
	int i;

	
	while (1)
	{
		line = read_line(shell);
		if (input_validation_pipes(shell, line) == 0 && input_validation_redir(shell, line) == 0 \
					&& check_input_quotes_pipe(shell,line) == 0)

	{
			line = change_to_space(line);
			split_line(line, shell);
			if (shell->cmds_count > 0)
			{
				i =0;
				while (i < shell->cmds_count)
				{
					if (if_it_is_builtins(&shell->cmds[i]) == 1)
					{
						if (shell->cmds->filetype[i] == NONE)
							builtins(shell, &shell->cmds[i]);
						if (shell->cmds[i].number_of_redir > 0)
						{
							if(shell->cmds->filetype[i] == OUT)
							{
								shell->parent_out= dup(STDOUT_FILENO);
								open_fd_out(&pipex, shell->cmds->filetype[i],*shell->cmds->filenames);
								check_filetype(&pipex,&shell->cmds[i]);
								builtins(shell, &shell->cmds[i]);
								if (dup2(shell->parent_out, STDOUT_FILENO)  < 0)
									dprintf(2, "dup2 \n");
								close(shell->parent_out);
							}
							if(shell->cmds->filetype[i] == IN)
							{
								shell->parent_in= dup(STDIN_FILENO);
								check_filetype(&pipex,&shell->cmds[i]);
								if (dup2(shell->parent_in, STDIN_FILENO)  < 0)
									dprintf(2, "dup2 \n");
								close(shell->parent_out);
							}
					}
						i++;
						continue;
					}
					if (shell->cmds_count >=1 && if_it_is_builtins(&shell->cmds[i]) == 0)
					{
						checking_path(shell, &pipex, i);
						piping(shell);
						forking(shell, pipex);
						closing(shell);
					}
				i++;
			}
			free(shell->cmds);
			}
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
		return (EXIT_SUCCESS);
	}
}
