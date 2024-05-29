/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newmain.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:52:26 by epolkhov          #+#    #+#             */
/*   Updated: 2024/05/29 20:50:41 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tok	split_line(char *line)
{
	t_tok	tokens;
	int		i;
	int		in_quote;

	tokens.pipe_tok = NULL;
	tokens.size = 0;
	in_quote = 0;
	i = 0;
	input_validation_pipes(line);
	input_validation_redir(line);
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
		perror("Syntax error: unclosed quotes");
		exit(1);
	}
	tokens.pipe_tok = do_split(line, 31);
	if (tokens.pipe_tok)
	{
		while (tokens.pipe_tok[tokens.size])
			tokens.size++;
	}
	printf("Number of tokens: %d\n", tokens.size);
	for (int j = 0; j < tokens.size; j++)
    {
        printf("Token %d: %s\n", j, tokens.pipe_tok[j]);
    }
	return (tokens);
}

char	*read_line(void)
{
	char	*input;

	input = readline("minishell-$ ");
	if (!input)
	{
		perror("Failed to read line");
		exit(EXIT_FAILURE);
	}
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
	t_tok	pipe_tok_str;

	while (1)
	{
		line = read_line();
		pipe_tok_str = split_line(line);
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
