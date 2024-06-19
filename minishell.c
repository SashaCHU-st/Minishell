/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:52:26 by epolkhov          #+#    #+#             */
/*   Updated: 2024/06/07 18:20:34 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	is_heredoc(line);
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

char	*read_line(void)
{
	char	*input;

	input = readline("minishell-$ ");
	if (!input)
		error_message("Failed to read line");
	else if (strcmp(input, "exit") == 0)
	{
		free(input);
		printf ("exit\n");
		exit(EXIT_SUCCESS);
	}
	
	add_history(input);
	printf("input: %s\n", input);
	return (input);
}

void	shell_loop(void)
{
	char	*line;
	//t_data	pipe_tok_str;

	//(void)pipe_tok_str;
	while (1)
	{
		line = read_line();
		if (input_validation_pipes(line) == 0 && input_validation_redir(line) == 0 \
					&& check_input_quotes_pipe(line) == 0)
			split_line(line);
		free (line);
	}
}

int	main(void)
{
	if (isatty(STDIN_FILENO))
		shell_loop();
	else
	{
		perror("Terminal is not in interactive mode");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}


