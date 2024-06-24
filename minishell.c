/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:52:26 by epolkhov          #+#    #+#             */
/*   Updated: 2024/06/24 16:04:57 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	check_input_quotes_pipe(char *line)
{
	int	i;
	int	in_quote;

	i = 0;
	in_quote = 0;
	while (line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			in_quote = !in_quote;
			i++;
			continue ;
		}
		if (line[i] == '|' && !in_quote)
			line[i] = 31;
		i++;
	}
	if ((in_quote || has_unclosed_quotes(line)))
	{
		ft_putendl_fd("Syntax error: unclosed quotes", 2);
		return (1);
	}
	return (0);
}

t_cmd	split_into_wtok(char *pipe_token)
{
	t_cmd	cmd;
	int		i;
	int		j;
	char	**words;
	t_cmd	new_words;

	cmd.word_tok = NULL;
	cmd.w_count = 0;
	i = 0;
	words = do_split(pipe_token, ' ');
	if (!words)
	{
		cmd.word_tok = NULL;
        cmd.w_count = 0;
		return (cmd);
	}
	while (words[i])
	{
		new_words.word_tok = malloc(sizeof(char *) * (cmd.w_count + 1));
		if (!new_words.word_tok)
			error_message("Failed to allocate memory");
		j = 0;
		while (j < cmd.w_count)
		{
			new_words.word_tok[j] = cmd.word_tok[j];
			j++;
		}
		new_words.word_tok[cmd.w_count] = ft_strdup(words[i]);
		if (!new_words.word_tok[cmd.w_count])
			error_message("Failed to duplicate string");
		free (cmd.word_tok);
		cmd.word_tok = new_words.word_tok;
		cmd.w_count++;
		i++;
	}
	f_free_array(words);
	return (cmd);
}

void	split_line(char *line)
{
	t_data	tokens;
	int		i;

	tokens.pipe_tok = NULL;
	tokens.cmds_count = 0;
	tokens.cmds = NULL;
	printf("input after replacing pipe: %s\n", line);
	//is_heredoc(line);
	tokens.pipe_tok = do_split(line, 31);
	if (!tokens.pipe_tok)
		return ;
	if (tokens.pipe_tok)
	{
		while (tokens.pipe_tok[tokens.cmds_count])
			tokens.cmds_count++;
	}
	tokens.cmds = (t_cmd *)malloc(sizeof(t_cmd) * tokens.cmds_count);
	if (!tokens.cmds)
		error_message("Failed to allocate memory");
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
	for (i = 0; i < tokens.cmds_count; i++) {
        for (int j = 0; j < tokens.cmds[i].w_count; j++) {
            free(tokens.cmds[i].word_tok[j]);
        }
        free(tokens.cmds[i].word_tok);
    }
    free(tokens.cmds);
    f_free_array(tokens.pipe_tok);
	//return (tokens);
}

// int if_builtins(t_built *data, int number_of_inputs)
// {
// 	if (ft_strncmp(data->inputs[0], "pwd", 4) == 0)
// 			ft_pwd();
// 	else if (ft_strncmp(data->inputs[0], "echo", 5) == 0)
// 			ft_echo(data, number_of_inputs);
// 	else if (ft_strncmp(data->inputs[0], "env", 4) == 0)
// 		ft_env(data);
// 	else if (ft_strncmp(data->inputs[0], "export", 7) == 0)
// 		ft_export(data, number_of_inputs);
// 	else if (ft_strncmp(data->inputs[0], "cd", 3) == 0)
// 		ft_cd(data, number_of_inputs);
// 	else if (ft_strncmp(data->inputs[0], "unset", 6) == 0)
// 			ft_unset(data, number_of_inputs);
// 	else
// 		return(0);
// 	return(1);
// }

char	*read_line(t_built *data)
{
	char	*input;
	int		number_of_inputs;
	t_pipex	pipex;
	char	*path;

	number_of_inputs = 0;
	input = readline("minishell-$ ");
	if (!input)
		error_message("Failed to read line");
	data->inputs = do_split(input, 32);
	while (data->inputs[number_of_inputs])
			number_of_inputs++;
	if (number_of_inputs > 0)
	{
		if(if_builtins(data, number_of_inputs) == 0)
		{
			path = mine_path(data);
			if(path)
				printf("%s\n", path);
			else 
				printf("KUKUUUUUUU");
			if (pipe(pipex.fd) == -1)
			{
				perror("Error in pipe()");
				exit(1);
			}
			pipex.commands_path = ft_split(path, ':');
			if (pipex.commands_path == 0)
			{
				close(pipex.fd[0]);
				close(pipex.fd[1]);
				free_fun(&pipex);
			}
			creating_children(&pipex, data, number_of_inputs);
			close(pipex.fd_in);
			close(pipex.fd_out);
		}
		else
			printf("HHHAHAHHAHAHAHAHAH");
	} 
	for (int i = 0; data->inputs[i] != NULL; i++)
		free(data->inputs[i]);
	free(data->inputs);
	add_history(input);
	printf("input: %s\n", input);
	return (input);
}

void	shell_loop(t_built *data)
{
	char	*line;
	//t_data	pipe_tok_str;

	//(void)pipe_tok_str;
	while (1)
	{
		line = read_line(data);
		if (input_validation_pipes(line) == 0 && input_validation_redir(line) == 0 \
					&& check_input_quotes_pipe(line) == 0)
			split_line(line);
		free (line);
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


