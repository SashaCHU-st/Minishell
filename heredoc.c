/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 10:05:10 by epolkhov          #+#    #+#             */
/*   Updated: 2024/07/15 12:52:02 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*hd_filename(t_data *shell, int count)
{
	char	*file;
	char	*temp;

	temp = ft_itoa(count);
	if (!temp)
		error_message(shell, "Failed to create file for heredoc", 1);
	file = ft_strjoin(".heredoc", temp);
	free (temp);
	if (!file)
		error_message(shell, "Failed to create file for heredoc", 1);
	return (file);
}

static int	hd_readline(char *line, t_data *tokens, char *delimeter, int fd)
{
	int	stdin;

	errno = 0;
	stdin = dup(STDIN_FILENO);
	if (stdin == -1)
		return (-1);
	while (1)
	{		
		if (signal_status)
		{
			free(line);
			dup2(stdin, STDIN_FILENO);
			close(stdin);
			return -1;
		}
		line = readline("> ");
		if (!line)
			break;
		if (ft_strcmp(line, delimeter) == 0)
		{
			free(line);
			break ;
		}
		if (ft_strchr(line, '$'))
			line = expand_var(tokens, line);
		ft_putendl_fd(line, fd);
		free(line);
	}
	if (errno && errno == EBADF)
	{
		dup2(stdin, STDIN_FILENO);
		close(stdin);
		return (-1);
	}
	return (0);
}

int	process_hd(t_data *tokens, const char *file, char *delimeter)
{
	int		fd;
	char	*line;

	line = NULL;
	get_signal(tokens, HEREDOC);
	unlink(file);
	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		error_message(tokens, "Failed to open fd for heredoc", 1);
	if (hd_readline(line, tokens, delimeter, fd) == -1)
	{
		close (fd);
		unlink(file);
		return (-1);
	}
	if (close(fd) == -1)
		error_message(tokens, "Failed to close fd for heredoc", 1);
	get_signal(tokens, DEFAULT);
	return (0);
}

void	*is_heredoc(char *line, t_data *tokens)
{
	int		i;
	int		j;
	int		len;
	int		in_quote;
	
	i = 0;
	in_quote = 0;
	tokens->hd_count = 0;
	signal_status = 0;
	while (line[i] && !signal_status)
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			in_quote = !in_quote;
			i++;
			continue;
		}
		if ((ft_strncmp(&line[i], "<<", 2) == 0) && !in_quote)
		{	
			tokens->hd_count++;
			printf("%d\n", tokens->hd_count);
			i = i + 2;
			while (check_space(line[i]))
				i++;
			j = i;
			len = 0;
			while (line[j] && line[j] != 31 && !check_space(line[j]))
			{
				len++;
				j++;
			}
			tokens->hd_delimeter = (char *)malloc(sizeof(char) * len + 1);
			if (tokens->hd_delimeter == NULL)
				error_message(tokens, "Memory allocation error\n", 1);
			j = 0;
			while (line[i] && line[i] != 31 && !check_space(line[i]))
			{
				if (line[i] == '\'' || line[i] == '\"')
					remove_quotes(line);
				tokens->hd_delimeter[j++] = line[i++];
			}
			tokens->hd_delimeter[j] = '\0';
			printf("delimeter Heredoc:%s\n", tokens->hd_delimeter);
			tokens->tempfile_hd = hd_filename(tokens, tokens->hd_count);
			printf("HD tempfile %s\n", tokens->tempfile_hd);
			if (!tokens->tempfile_hd)
				error_message(tokens, "Failed to assign filename for heredoc", 1);
			if (process_hd(tokens, tokens->tempfile_hd, tokens->hd_delimeter) == -1)
			{
				free(tokens->hd_delimeter);
				tokens->hd_delimeter = NULL;
				break ;
			}
			if (tokens->hd_delimeter != NULL)
				free(tokens->hd_delimeter);
		}
		if (line[i] != '\0')
			i++;
	}
	return (0);
}

