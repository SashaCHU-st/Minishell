/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-02 15:49:10 by epolkhov          #+#    #+#             */
/*   Updated: 2024-07-02 15:49:10 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

static e_filetype peek(char *line, int index)
{
	if (line[index] == '<' && line[index + 1] == '<') 
		return (HERE);
	if (line[index] == '<')
		return (IN);
	if (line[index] == '>' && line[index + 1] == '>')
		return (APPEND);
	if (line[index] == '>')
		return (OUT);
	return (NONE);
}


static char *take_filename(char *line, int *index)
{
	int		start;
	char	*filename;

	while (check_space(line[*index]))
		(*index)++;
	start = *index;
	while (line[*index] && !check_space(line[*index]) && line[*index] != '<' && \
			 line[*index] != '>' && line[*index] != 31)
		(*index)++;
	filename = ft_strndup(&line[start], *index - start);
	return (filename);
}

void    make_redirs(t_data *tokens)
{
	int			i;
	int			j;
	char		*line;
	e_filetype	type;
	int			redir_count;
	char		*filename;
	int			hd_index;

	i = -1;
	hd_index = 1;
	while (tokens->pipe_tok[++i] &&  i < tokens->cmds_count)
	{
		j = 0;
		line = tokens->pipe_tok[i];
		redir_count = 0;
		tokens->cmds[i].filenames = malloc(sizeof(char *) * (ft_strlen(line) + 1));
		tokens->cmds[i].filetype = malloc(sizeof(int) * (ft_strlen(line) + 1));
		if (!tokens->cmds[i].filenames || !tokens->cmds[i].filetype)
			error_message("Memory allocation error");
		while (line[j])
		{
			type = peek(line, j);
			if (type != NONE)
			{
				
				if (type == HERE || type == APPEND)
					j += 2;
				else
					j++;
				while (check_space(line[j]))
					j++;
				filename = take_filename(line, &j);
				printf("Filename: %s\n", filename);
				if (filename)
				{
					if (type == HERE)
						tokens->cmds[i].filenames[redir_count] = hd_filename(hd_index++);
					else
						tokens->cmds[i].filenames[redir_count] = filename;
					printf("Array filename %d:  %s\n", redir_count, tokens->cmds[i].filenames[redir_count]);
					printf("Type: %d\n", type);
					tokens->cmds[i].filetype[redir_count] = type;
					printf("FILEtype %d\n", tokens->cmds[i].filetype[redir_count]);
					printf("Redir count: %d\n",  redir_count);
					redir_count++;
				}
				else
					ft_putendl_fd("Syntax error: no filename", 2);
			}
			else
				j++;

		}
		tokens->cmds[i].filenames[redir_count] = NULL;
		tokens->cmds[i].filetype[redir_count] = NONE;
		tokens->cmds[i].number_of_redir = redir_count;
		printf("Redir count: %d\n",  tokens->cmds[i].number_of_redir);
	}
}

void	remove_redir_from_input(t_data *tokens)
{
	char	*line;
	char	*new_line;
	int		i;
	int		j;
	int		k;
	int		in_single_quote;
	int		in_double_quote;
	int		in_quotes;

	i = -1;
	while (tokens->pipe_tok[++i] &&  i < tokens->cmds_count)
	{
		line = tokens->pipe_tok[i];
		new_line = (char *)malloc(sizeof(char) * (ft_strlen(line) + 1));
		if (!new_line)
			error_message("Failed to malloc for newline");
		j = 0;
		k = 0;
		in_single_quote = 0;
		in_double_quote = 0;
		while (line[j])
		{
			in_quotes = is_in_quotes(line[j], &in_single_quote, &in_double_quote);
			if ((line[j] == '<' || line[j] == '>') && !in_quotes)
			{
				if ((line[j] == '<' && line[j + 1] == '<' ) || (line[j] == '>' && line[j + 1] == '>'))
					j += 2;
				else
					j++;
				while (check_space(line[j]))
					j++;
				while (line[j] && line[j] != '<' && \
						line[j] != '>' && line[j] != 31 && line[j] != ' ')
					j++;
			}
			else
				new_line[k++] = line[j++];
			//j++;
			//k++;	
		}
		new_line[k] = '\0';
		free(tokens->pipe_tok[i]);
		tokens->pipe_tok[i] = new_line;
		//free(line);
		//free(new_line);
	}
}
