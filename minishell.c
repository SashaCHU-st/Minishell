/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:52:26 by epolkhov          #+#    #+#             */
/*   Updated: 2024/06/10 21:49:48 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_input_quotes_pipe(char *line)
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
		if (!in_quote)
		{
			if (line[i] == '|')
				line[i] = 31;
		}
		i++;
	}
	if ((in_quote || has_unclosed_quotes(line)))
		error_message("Syntax error: unclosed quotes");
}

// char	*hd_filename(int count)
// {
// 	char	*file;
// 	char	*temp;

// 	temp = ft_itoa(count);
// 	if (!temp)
// 		error_message("Failed to create file for heredoc");
// 	file = ft_strjoin(".heredoc", temp);
// 	free (temp);
// 	if (!file)
// 		error_message("Failed to create file for heredoc");
// 	return (file);
// }

// void	process_hd(const char *file, const char *delimeter)
// {
// 	int	fd;
// 	char	*line;

// 	unlink(file);
// 	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
// 	if (fd == -1)
// 		error_message("Failed to open fd for heredoc");
// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (!line && strcmp(line, delimeter) == 0)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		ft_putendl_fd(line, fd);
// 		free(line);
// 	}
// 	if (close(fd) == -1)
// 		error_message("Failed to close fd for heredoc");
// }

// void	*is_heredoc(char *line)
// {
// 	int		i;
// 	t_tok	str_delimeter;
// 	int		j;
// 	int		len;
// 	t_tok	count;
// 	int	in_quote = 0;
// 	t_tok	file;

// 	str_delimeter.hd_delimeter = NULL;
// 	i = 0;
// 	len = 0;
// 	count.hd_index = 0;

// 	while (line[i])
// 	{
// 		if (line[i] == '\"' || line[i] == '\'')
//         {
//             in_quote = !in_quote;
//             i++;
//             continue;
//         }
// 		if ((ft_strncmp(&line[i], "<<", 2) == 0) && !in_quote)
// 		{
// 			count.hd_index++;
// 			printf("%d\n", count.hd_index);
// 			i = i + 2;
// 			while (check_space(line[i]))
// 				i++;
// 			j = i;
// 			while (line[j] && line[j] != 31 && !check_space(line[j]))
// 			{
// 				len++;
// 				j++;
// 			}
// 			str_delimeter.hd_delimeter = (char *)malloc(sizeof(char) * len + 1);
// 			if (str_delimeter.hd_delimeter == NULL)
// 				error_message("Memory allocation error\n");
// 			j = 0;
// 			while (line[i] && line[i] != 31 && !check_space(line[i]))
// 				str_delimeter.hd_delimeter[j++] = line[i++];
// 			str_delimeter.hd_delimeter[j] = '\0';
// 			printf("delimeter Heredoc:%s\n", str_delimeter.hd_delimeter);
// 			if (str_delimeter.hd_delimeter != NULL)
// 				free(str_delimeter.hd_delimeter);
// 			file.tempfile_hd = hd_filename(count.hd_index);
// 			if (!file.tempfile_hd)
// 				error_message("Failed to assign filename for heredoc");
// 			process_hd(file.tempfile_hd, str_delimeter.hd_delimeter);
// 			free(str_delimeter.hd_delimeter);
// 		}
// 		else
// 			i++;
// 	}
// 	return (NULL);
// }

t_tok	split_line(char *line)
{
	t_tok	tokens;

	tokens.pipe_tok = NULL;
	tokens.size = 0;
	input_validation_pipes(line);
	input_validation_redir(line);
	check_input_quotes_pipe(line);
	printf("input after replacing pipe: %s\n", line);
	is_heredoc(line);
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
