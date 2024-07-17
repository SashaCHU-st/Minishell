/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:49:10 by epolkhov          #+#    #+#             */
/*   Updated: 2024/07/17 17:19:44 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

static e_filetype	peek(char *line, int index)
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

static char	*take_filename(char *line, int *index)
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

void	creating_filename(int j, char *line, int i, t_data *sh)
{
	j = 0;
	sh->redir_count = 0;
	line = sh->pipe_tok[i];
	sh->cmds[i].filenames = malloc(sizeof(char *) * (ft_strlen(line) + 1));
	sh->cmds[i].filetype = malloc(sizeof(int) * (ft_strlen(line) + 1));
	if (!sh->cmds[i].filenames || !sh->cmds[i].filetype)
		error_message(sh, "Memory allocation error", 1);
	while (line[j])
	{
		sh->cmds[i].type = peek(line, j);
		if (sh->cmds[i].type != NONE)
		{
			if (sh->cmds[i].type == HERE || sh->cmds[i].type == APPEND)
				j += 2;
			else
				j++;
			while (check_space(line[j]))
				j++;
			sh->filename = take_filename(line, &j);
			if (sh->filename)
			{
				if (sh->cmds[i].type == HERE)
					sh->cmds[i].filenames[sh->redir_count] = hd_filename(sh,
							sh->hd_index++);
				else
					sh->cmds[i].filenames[sh->redir_count] = sh->filename;
				sh->cmds[i].filetype[sh->redir_count] = sh->cmds[i].type;
				sh->redir_count++;
			}
			else
				ft_putendl_fd("Syntax error: no filename", 2);
		}
		else
			j++;
	}
}

void	removing(t_data *sh, int j, int k, int i)
{
	sh->line = sh->pipe_tok[i];
	sh->new_line = (char *)malloc(sizeof(char) * (ft_strlen(sh->line) + 1));
	if (!sh->new_line)
		error_message(sh, "Failed to malloc for newline", 1);
	j = 0;
	k = 0;
	sh->in_single_quote = 0;
	sh->in_double_quote = 0;
	while (sh->line[j])
	{
		sh->in_quotes = is_in_quotes(sh->line[j], &sh->in_single_quote,
				&sh->in_double_quote);
		if ((sh->line[j] == '<' || sh->line[j] == '>') && !sh->in_quotes)
		{
			if ((sh->line[j] == '<' && sh->line[j + 1] == '<' )
				|| (sh->line[j] == '>' && sh->line[j + 1] == '>'))
				j += 2;
			else
				j++;
			while (check_space(sh->line[j]))
				j++;
			while (sh->line[j] && sh->line[j] != '<'
				&& sh->line[j] != '>' && sh->line[j] != 31
				&& sh->line[j] != ' ')
				j++;
		}
		else
			sh->new_line[k++] = sh->line[j++];
	}
	sh->new_line[k] = '\0';
	free(sh->pipe_tok[i]);
	sh->pipe_tok[i] = sh->new_line;
}