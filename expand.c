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

static int	end_character(char c)
{
	return (c == '\0' || c == ' ' || c == '$'
		|| c == '\"' || c == '\'' || c == '=' || c == ':');
}

static char	*receive_exit_status(t_data *shell)
{
	char	*status;

	if (shell->exit_status > 255)
		status = ft_itoa(WEXITSTATUS(shell->exit_status));
	else
		status = ft_itoa(shell->exit_status);
	if (!status)
		error_message(shell, "Malloc failed", 1);
	return (status);
}

static char	*get_expand(t_data *shell, char *line)
{
	int		len;
	char	*value;
	char	*env;

	len = 0;
	if (line[len] == '?')
	{
		printf("ststus\n");
		return (receive_exit_status(shell));
	}
	while (!end_character(line[len]))
		len++;
	if (len == 0)
		return (ft_strdup(""));
	env = (char *)malloc(sizeof(char) * len + 1);
	if (!env)
		error_message(shell, "Malloc failed", 1);
	ft_strncpy(env, line, len);
	env[len] = '\0';
	value = ft_getenv(shell, env);
	printf("I received: %s \n", value);
	free (env);
	if (!value)
		value = ft_strdup("");
	return (value);
}

static char	*expand_env(t_data *shell, char **line, int *i)
{
	int		st;
	char	*value;
	char	*new_line;
	int		new_line_len = 0;
	
	st = (*i) + 1;
	printf("value before expand: %s\n", *line);
	printf("value before expand: %c\n", (*line)[st]);
	value = get_expand(shell, &(*line)[st]);
	printf("value: %s\n", value);
	if (!value)
		error_message(shell, "Expansion of env failed", 1);
	shell->var_len = 0;
	while (!end_character((*line)[st + shell->var_len]))
		shell->var_len++;
	new_line_len = ft_strlen(value) + ft_strlen(*line) - shell->var_len - 1;
	if (new_line_len < 0)
		new_line_len = 0;
	new_line = (char *)malloc(sizeof(char) * (new_line_len + 1));
	if (!new_line)
	{
		free(value);
		error_message(shell, "Failed to malloc", 1);
	}
	ft_strncpy(new_line, *line, (*i));
	new_line[(*i)] = '\0';
	strcpy(new_line + (*i), value);
	strcpy(new_line + (*i) + ft_strlen(value), *line + st + shell->var_len);
	new_line[new_line_len] = '\0';
	free(value);
	return (new_line);
}

char	*expand_var(t_data *shell, char *line)
{
	int	j;

	j = 0;
	while (line[j])
	{
		if (line[j] == '\"')
			shell->in_dquotes = !shell->in_dquotes;
		if (line[j + 1] && line[j] == '\'' && !shell->in_dquotes)
			j = skip_quotes(line, j);
		if (line[j] == '$' && line[j + 1] && line[j + 1] != ' '
			&& line[j + 1] != '$' && (ft_isdigit(line[j + 1]) || ft_isalpha(line[j + 1]) || line[j + 1] == '?'))
		{
			shell->expanded_line = expand_env(shell, &line, &j);
			if (!shell->expanded_line)
			{
				ft_putendl_fd("Failed to expand", 2);
				free(line);
				return (NULL);
			}
			free(line);
			line = shell->expanded_line;
		}
		else
			j++;
	}
	return (line);
}
