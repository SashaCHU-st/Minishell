/* ************************************************************************** */
/*                                                                        */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-02 15:29:37 by epolkhov          #+#    #+#             */
/*   Updated: 2024-07-02 15:29:37 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

static int end_character(char c)
{
	return (c == '\0' || c == ' ' || c == '$'
	|| c == '\"' || c == '\'' || c == '=' || c == ':');
}

static char *get_expand(char *line)
{
	int		len;
	char	*value;
	char	*env;

	len =  0;
	// if (line[len] == '?')
		// return get_exit_status();
	while (!end_character(line[len]))
		len++;
	if (len == 0)
		return (ft_strdup(""));
	env = (char *)malloc(sizeof(char) * len + 1);
	if (!env)
   		error_message("Malloc filed");
	ft_strncpy(env, line, len);
	env[len] = '\0';
	value = getenv(env);
	if(value)
		return (ft_strdup(value));
	else
		return (ft_strdup(""));
}

static char	*expand_env(char **line, int *i)
{
	int		start;
	char	*value;
	char	*new_line;
	int		var_name_len;
	int		new_line_len;

	start = (*i) + 1;
	var_name_len = 0;
	value = get_expand(&(*line)[start]);
	printf("Value got : %s\n", value);
	if (!value)
		error_message("Expansion of env failed");
	while (!end_character((*line)[start + var_name_len]))
		var_name_len++;
	new_line_len = ft_strlen(value) + ft_strlen(*line) - var_name_len - 1;
	new_line = (char *)malloc(sizeof(char) * new_line_len + 1);
	if (!new_line)
	{
		free(value);
		error_message("Failed to malloc");
	}
	ft_strncpy(new_line, *line, (*i));
	ft_strncpy(new_line + (*i), value, ft_strlen(value));
	ft_strncpy(new_line + (*i) + ft_strlen(value), *line + start + var_name_len, ft_strlen(*line) - start - var_name_len);
	new_line[new_line_len] = '\0';
	printf("newline 3: %s \n", new_line);
	free(value);
	return (new_line);
}

char	*expand_var(char *line)
{
	//char	*line;
	//int		i;
	int		j;
	int		in_dquotes;
	char	*expanded_line;

	//i = -1;
	in_dquotes = 0;
	//while (tokens->pipe_tok[++i] && i < tokens->cmds_count)
	//{
		//line = tokens->pipe_tok[i];
		j = 0;
		while (line[j])
		{
			if (line[j] == '\"')
				in_dquotes = !in_dquotes;
			if (line[j + 1] && line[j] == '\'' && !in_dquotes)
			{
				j = skip_quotes(line, j);
			}
			if (line[j + 1] && line[j] == '$' && line[j + 1] != ' ')
			{
				expanded_line = expand_env(&line, &j);
				if (!expanded_line)
				{
					ft_putendl_fd("Failed to expand", 2);
					return(NULL);
				}
				//free(tokens->pipe_tok[i]);
				line = expanded_line;
			}
			j++;
		}
		return (line);
	//}	
}
