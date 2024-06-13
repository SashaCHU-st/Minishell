/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-12 10:05:10 by epolkhov          #+#    #+#             */
/*   Updated: 2024-06-12 10:05:10 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*hd_filename(int count)
{
	char	*file;
	char	*temp;

	temp = ft_itoa(count);
	if (!temp)
		error_message("Failed to create file for heredoc");
	file = ft_strjoin(".heredoc", temp);
	free (temp);
	if (!file)
		error_message("Failed to create file for heredoc");
	return (file);
}

void	process_hd(const char *file, const char *delimeter)
{
	int	fd;
	char	*line;

	unlink(file);
	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		error_message("Failed to open fd for heredoc");
	while (1)
	{
		line = readline("> ");
        if (!line)
            break;
		if (strcmp(line, delimeter) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	if (close(fd) == -1)
		error_message("Failed to close fd for heredoc");
}

void    *is_heredoc(char *line)
{
	int		i;
	t_tok	str_delimeter;
	int		j;
	int		len;
	t_tok	count;
	int	in_quote = 0;
	t_tok	file;

	str_delimeter.hd_delimeter = NULL;
	i = 0;
	len = 0;
	count.hd_index = 0;

	while (line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
        {
            in_quote = !in_quote;
            i++;
            continue;
        }
		if ((ft_strncmp(&line[i], "<<", 2) == 0) && !in_quote)
		{
			count.hd_index++;
			printf("%d\n", count.hd_index);
			i = i + 2;
			while (check_space(line[i]))
				i++;
			j = i;
			while (line[j] && line[j] != 31 && !check_space(line[j]))
			{
				len++;
				j++;
			}
			str_delimeter.hd_delimeter = (char *)malloc(sizeof(char) * len + 1);
			if (str_delimeter.hd_delimeter == NULL)
				error_message("Memory allocation error\n");
			j = 0;
			while (line[i] && line[i] != 31 && !check_space(line[i]))
				str_delimeter.hd_delimeter[j++] = line[i++];
			str_delimeter.hd_delimeter[j] = '\0';
			printf("delimeter Heredoc:%s\n", str_delimeter.hd_delimeter);
			
			file.tempfile_hd = hd_filename(count.hd_index);
			if (!file.tempfile_hd)
				error_message("Failed to assign filename for heredoc");
			process_hd(file.tempfile_hd, str_delimeter.hd_delimeter);
            if (str_delimeter.hd_delimeter != NULL)
			    free(str_delimeter.hd_delimeter);
		}
        if (line[i] != '\0')
		    i++;
	}
	return (0);
}