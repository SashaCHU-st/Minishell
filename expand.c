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

static char	*get_expand(t_data *shell, char *line)
{
	int		len;
	char	*value;
	char	*env;

	len = 0;
	if (line[len] == '?')
		return (receive_exit_status(shell));
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
	free (env);
	if (!value)
		value = ft_strdup("");
	return (value);
}

static int	cal_new_line_len(t_data *shell, char *line, char *value, int i)
{
	int	st;
	int	new_line_len;

	st = i + 1;
	shell->var_len = 0;
	new_line_len = 0;
	while (!end_character(line[st + shell->var_len]))
		shell->var_len++;
	new_line_len = ft_strlen(value) + ft_strlen(line) - shell->var_len - 1;
	if (new_line_len < 0)
		return (0);
	else
		return (new_line_len);
}

static char	*expand_env(t_data *shell, char **line, int *i)
{
	int		st;
	char	*value;
	char	*new_line;
	int		new_line_len;

	st = (*i) + 1;
	value = get_expand(shell, &(*line)[st]);
	if (!value)
	{
		error_message(shell, "Expansion of env failed", 1);
		return (NULL);
	}
	new_line_len = cal_new_line_len(shell, *line, value, *i);
	new_line = (char *)malloc(sizeof(char) * (new_line_len + 1));
	if (!new_line)
	{
		free(value);
		error_message(shell, "Failed to malloc", 1);
		return (NULL);
	}
	ft_strncpy(new_line, *line, (*i));
	new_line[(*i)] = '\0';
	ft_strcpy(new_line + (*i), value);
	ft_strcpy(new_line + (*i) + ft_strlen(value), *line + st + shell->var_len);
	new_line[new_line_len] = '\0';
	free(value);
	return (new_line);
}

void	test(t_data *shell, char *line)
{
	if (!shell->expanded_line)
	{
		ft_putendl_fd("Failed to expand", 2);
		free(line);
		shell->expanded_line = NULL;
	}
}

char	*expand_var(t_data *shell, char *line)
{
	int		j;

	j = 0;
	while (line[j])
	{
		if (line[j] == '\"')
			shell->in_dquotes = !shell->in_dquotes;
		if (line[j + 1] && line[j] == '\'' && !shell->in_dquotes)
			j = skip_quotes(line, j);
		if (line[j] == '$' && line[j + 1] && line[j + 1] != ' ' && \
			line[j + 1] != '$' && (ft_isdigit(line[j + 1]) || \
			ft_isalpha(line[j + 1]) || line[j + 1] == '?' || \
			line[j + 1] == '\"'))
		{
			shell->expanded_line = expand_env(shell, &line, &j);
			test(shell, line);
			if (!shell->expanded_line)
				return (NULL);
			free(line);
			line = shell->expanded_line;
		}
		j++;
	}
	return (line);
}