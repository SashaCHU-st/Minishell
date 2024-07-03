/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:52:26 by epolkhov          #+#    #+#             */
/*   Updated: 2024/07/02 15:13:43 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

t_cmd	split_into_wtok(char *pipe_token)
{
	t_cmd	cmd;

	cmd.word_tok = NULL;
	cmd.w_count = 0;
	change_space_to_31(pipe_token);
	remove_quotes(pipe_token);
	cmd.word_tok = do_split(pipe_token, 31);
	if (!cmd.word_tok)
		return (cmd);
	while (cmd.word_tok[cmd.w_count])
		cmd.w_count++;
	return (cmd);
}

void	init_t_data(t_data *tokens)
{
	tokens->pipe_tok = NULL;
	tokens->cmds_count = 0;
	tokens->cmds = NULL;
	tokens->hd_delimeter = NULL;
	tokens->hd_count = 0;
	tokens->tempfile_hd = NULL;
}

void init_cmd(t_cmd *cmd)
{
	if (cmd == NULL)
		return;

	cmd->filenames = NULL;
	cmd->filetype = NULL;
	cmd->number_of_redir = 0;
	cmd->w_count = 0;
	cmd->word_tok = NULL;
}

t_data	split_line(char *line)
{
	t_data	tokens;
	int		i;

	init_t_data(&tokens);
	printf("input after replacing pipe: %s\n", line);
	is_heredoc(line, &tokens); // is_heredoc(line, t_data *tokens);
	tokens.pipe_tok = do_split(line, 31);
	if (!tokens.pipe_tok)
		return (tokens);
	if (tokens.pipe_tok)
	{
		while (tokens.pipe_tok[tokens.cmds_count])
			tokens.cmds_count++;
	}
	tokens.cmds = (t_cmd *)malloc(sizeof(t_cmd) * tokens.cmds_count);
	if (!tokens.cmds)
		error_message("Failed to allocate memory");
	i = -1;
	while (++i < tokens.cmds_count)
	{
		init_cmd(&tokens.cmds[i]);
		//i++;
	}
	make_redirs(&tokens);
	remove_redir_from_input(&tokens);
	i = -1;
	while (tokens.pipe_tok[++i] && i < tokens.cmds_count)
	{
		tokens.pipe_tok[i] = expand_var(tokens.pipe_tok[i]);
	}
	i = 0;
    while (i < tokens.cmds_count) {
        int j = 0;
        while (tokens.cmds[i].filenames[j])
		{
            tokens.cmds[i].filenames[j] = expand_var(tokens.cmds[i].filenames[j]);
			printf("Expand filename %d: %s\n", j, tokens.cmds[i].filenames[j]);
            if (!tokens.cmds[i].filenames[j])
			{
                ft_putendl_fd("Variable expansion failed in filenames", 2);
                exit(EXIT_FAILURE);
            }
            j++;
        }
        i++;
    }

	for (int j = 0; j < tokens.cmds_count; j++)
	{
		printf("Token after redir remove %d: %s\n", j, tokens.pipe_tok[j]);
    }
	i = 0;
	while (i < tokens.cmds_count)
	{
		
		tokens.cmds[i] = split_into_wtok(tokens.pipe_tok[i]);
		i++;
	}


	printf("Number of tokens: %d\n", tokens.cmds_count);
	for (int j = 0; j < tokens.cmds_count; j++)
	{
		printf("Token %d: %s\n", j, tokens.pipe_tok[j]);
	}
	
	for (i = 0; i < tokens.cmds_count; i++) {
		printf("Command %d:\n", i);
		
		for (int j = 0; j < tokens.cmds[i].w_count; j++) {
			printf("  Word %d: %s\n", j, tokens.cmds[i].word_tok[j]);
		}
		
	}
	
	// for (i = 0; i < tokens.cmds_count; i++) {
	//	 for (int j = 0; j < tokens.cmds[i].w_count; j++) {
	//		 free(tokens.cmds[i].word_tok[j]);
	//	 }
	//	 free(tokens.cmds[i].word_tok);
	// }
	// free(tokens.cmds);
	// f_free_array(tokens.pipe_tok);
	return (tokens);
}

 int if_builtins(t_built *data, t_cmd *cmd)
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

char	*read_line(t_built *line)
{
	char	*input;

	(void)line;
	input = readline("minishell-$ ");
	if (!input)
		error_message("Failed to read line");
	if (ft_strncmp(input, "exit", 5) == 0)
	{
		free(input);
		printf ("exit\n");
		exit(EXIT_SUCCESS);
	}
	add_history(input);
	printf("input: %s\n", input);
	return (input);
}

void	check_permissions(t_built *shell)
{
	if (shell->data.cmds->word_tok[2][0] == '\0' || shell->data.cmds->word_tok[3][0] == '\0')
//	if (shell->data.cmds->word_tok[2][0] == '\0')
	{
		write(2, "zsh: permission denied:\n", 24);
	}
	else if (shell->data.cmds->word_tok[2][0] == '\0' && shell->data.cmds->word_tok[3][0] == '\0')
	//else if (shell->data.cmds->word_tok[2][0] == '\0')
	{
		write(2, "zsh: permission denied:\n", 24);
		exit(1);
	}
}


void shell_loop(t_built *shell)
{
	char	*line;
	t_pipex	pipex;
	char	*path;
	int i;
	while (1)
	{
		line = read_line(shell);
		if (input_validation_pipes(line) == 0 && input_validation_redir(line) == 0 \
					&& check_input_quotes_pipe(line) == 0)
		{
			line = change_to_space(line);
			shell->data = split_line(line);
			if (shell->data.cmds_count > 0)
			{
				i = 0;
				while (i < shell->data.cmds_count)
				{
					if (if_builtins(shell, &shell->data.cmds[i]) == 1)
					{
						i++;
						continue;
					}
					else if (shell->data.cmds->w_count >=1 && if_builtins(shell, &shell->data.cmds[i]) == 0)
					{
					path = mine_path(shell);
					if(shell->data.cmds->w_count == 4)
					{
						printf("hellooo\n");
						if (pipe(pipex.fd) == -1)
					{
						perror("Error in pipe()");
						exit(1);
					}
					}
					pipex.commands_path = ft_split(path, ':');
					if (pipex.commands_path == NULL)
					{
						close(pipex.fd[0]);
						close(pipex.fd[1]);
						free_fun(&pipex);
						i++;
					}
					creating_children(&pipex, shell, shell->data.cmds->w_count);
					close(pipex.fd_in);
					close(pipex.fd_out);
					}
				else 
					printf("HELLO_WORLD\n");
				i++;
				}
			free(shell->data.cmds);
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
	t_built data;
	(void)argv;
	data.envp = copy_envp(envp);
	if(argc < 2)
	{
		if (isatty(STDIN_FILENO))
			shell_loop(&data);
		else
		{
			perror("Terminal is not in interactive mode");
			return (EXIT_FAILURE);
		}
		return (EXIT_SUCCESS);
	}
}
