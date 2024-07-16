/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:49:10 by epolkhov          #+#    #+#             */
/*   Updated: 2024/07/13 13:55:42 by aheinane         ###   ########.fr       */
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
	if (start == *index)
		return (NULL);
	filename = ft_strndup(&line[start], *index - start);
	return (filename);
}


void    make_redirs(t_data *tokens)
{
	int			i;
	int			j;
	char		*line;
	char		*filename;
	int			hd_index;

	i = -1;
	hd_index = 1;
	while (tokens->pipe_tok[++i] &&  i < tokens->cmds_count)
	{
		j = 0;
		tokens->redir_count = 0;
		line = tokens->pipe_tok[i];
		tokens->cmds[i].filenames = malloc(sizeof(char *) * (ft_strlen(line) + 1));
		tokens->cmds[i].filetype = malloc(sizeof(int) * (ft_strlen(line) + 1));
		if (!tokens->cmds[i].filenames || !tokens->cmds[i].filetype)
			error_message(tokens, "Memory allocation error", 1);
		// ft_memset(tokens->cmds[i].filenames, 0, sizeof(char *) * (ft_strlen(line) + 1));
        // ft_memset(tokens->cmds[i].filetype, 0, sizeof(int) * (ft_strlen(line) + 1));

		while (line[j])
		{
		tokens->cmds[i].type = peek(line, j);
			if (tokens->cmds[i].type != NONE)
			{
				if (tokens->cmds[i].type == HERE || tokens->cmds[i].type == APPEND)
					j += 2;
				else
					j++;
				while (check_space(line[j]))
					j++;
				filename = take_filename(line, &j);
				if (filename)
				{
					if (tokens->cmds[i].type == HERE)
						tokens->cmds[i].filenames[tokens->redir_count] = hd_filename(tokens, hd_index++);
					else
						tokens->cmds[i].filenames[tokens->redir_count] = filename;
					tokens->cmds[i].filetype[tokens->redir_count] = tokens->cmds[i].type;
					tokens->redir_count++;
				}
				else
					ft_putendl_fd("Syntax error: no filename", 2);
			}
			else
				j++;
		}
		tokens->cmds[i].filenames[tokens->redir_count] = NULL;
		tokens->cmds[i].filetype[tokens->redir_count] = NONE;
		tokens->cmds[i].number_of_redir = tokens->redir_count;
		//free (line);
	}
	  for (int k = 0; k < tokens->cmds_count; ++k) {
    //     for (int l = 0; l < tokens->cmds[k].number_of_redir; ++l) {
    //         if (tokens->cmds[k].filetype[l] == HERE) {
    //             free(tokens->cmds[k].filenames[l]);  // Freeing filenames for HERE
    //         }
    //     }
        // free(tokens->cmds[k].filenames);
        // free(tokens->cmds[k].filetype);
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
			error_message(tokens, "Failed to malloc for newline", 1);
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
		}
		new_line[k] = '\0';
		free(tokens->pipe_tok[i]);
		tokens->pipe_tok[i] = new_line;
	}
}
