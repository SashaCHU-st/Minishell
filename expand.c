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

char	*ft_getenv(t_data *shell, char *env)
{
	char	*new_env;
	int		i;
	int		len;

	i = -1;
	if (!env || !*env)
		return (NULL);
	len = ft_strlen(env);
	while (shell->envp[++i])
	{
		if (!ft_strncmp(shell->envp[i], env, len))
		{
			if(shell->envp[i][len] == '=')
			{
				new_env = ft_strdup(shell->envp[i] + len + 1);
				if (!new_env)
					error_message(shell, "Failed to malloc env", 1);
				return (new_env);
			}
		}
	}
	return (NULL);
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

static char *get_expand(t_data *shell, char *line)
{
	int		len;
	char	*value;
	char	*env;

	len =  0;
	if (line[len] == '?')
		return receive_exit_status(shell);
	while (!end_character(line[len]))
		len++;
	if (len == 0)
		return (ft_strdup(""));
	env = (char *)malloc(sizeof(char) * len + 1);
	if (!env)
   		error_message(shell, "Malloc filed", 1);
	ft_strncpy(env, line, len);
	env[len] = '\0';
	value = ft_getenv(shell, env);
	free (env);
	if(!value)
		value = ft_strdup("");
	return (value);
}

static char	*expand_env(t_data *shell, char **line, int *i)
{
	int		start;
	char	*value;
	char	*new_line;
	int		var_name_len;
	int		new_line_len;

	start = (*i) + 1;
	var_name_len = 0;
	value = get_expand(shell, &(*line)[start]);
	if (!value)
		error_message(shell, "Expansion of env failed", 1);
	while (!end_character((*line)[start + var_name_len]))
		var_name_len++;
	new_line_len = ft_strlen(value) + ft_strlen(*line) - var_name_len - 1;
	new_line = (char *)malloc(sizeof(char) * new_line_len + 1);
	if (!new_line)
	{
		free(value);
		error_message(shell, "Failed to malloc", 1);
	}
	ft_strncpy(new_line, *line, (*i));
	ft_strncpy(new_line + (*i), value, ft_strlen(value));
	ft_strncpy(new_line + (*i) + ft_strlen(value), *line + start + var_name_len, \
				 ft_strlen(*line) - start - var_name_len);
	new_line[new_line_len] = '\0';
	free(value);
	return (new_line);
}

char	*expand_var(t_data *shell, char *line)
{
	int		j;
	int		in_dquotes;
	char	*expanded_line;

	in_dquotes = 0;
	j = 0;
	while (line[j])
	{
		if (line[j] == '\"')
			in_dquotes = !in_dquotes;
		if (line[j + 1] && line[j] == '\'' && !in_dquotes)
			j = skip_quotes(line, j);
		if (line[j] == '$'&& line[j + 1] && line[j + 1] != ' ' && line[j + 1] != '$')
		{
			expanded_line = expand_env(shell, &line, &j);
			if (!expanded_line)
			{
				ft_putendl_fd("Failed to expand", 2);
				free(line);
				return(NULL);
			}
			free(line);
			line = expanded_line;
		}
		j++;
	}
	return (line);
}
