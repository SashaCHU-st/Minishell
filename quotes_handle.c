/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-26 10:45:47 by epolkhov          #+#    #+#             */
/*   Updated: 2024-06-26 10:45:47 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	skip_quotes(char *line, int i)
{
	char	quote;

	quote = line[i];
	i++;
	while (line[i] && line[i] != quote)
		i++;
	return (i);
}

bool	has_unclosed_quotes(char *line)
{
	int		i;
	bool	single_quote_open;
	bool	double_quote_open;

	single_quote_open = false;
	double_quote_open = false;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			single_quote_open = !single_quote_open;
		else if (line[i] == '\"')
			double_quote_open = !double_quote_open;
		i++;
	}
	if (single_quote_open || double_quote_open)
		return (true);
	return (false);
}

static void copy_before_remove(char *str, bool in_singles, bool in_doubles)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_doubles)
		{
			in_singles = !in_singles;
			i++;
			continue;
        }
		if (str[i] == '\"' && !in_singles)
		{
			in_doubles = !in_doubles;
			i++;
			continue;
		}
		str[j] = str[i];
		i++;
		j++;
	}
	str[j] = '\0';
}

void	remove_quotes(char *str)
{
	bool inside_singles;
	bool inside_doubles;

	inside_doubles = false;
	inside_singles = false;
	if (!str)
		return ;
	copy_before_remove(str, inside_singles, inside_doubles);
}

int	check_input_quotes_pipe(t_data *shell, char *line)
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
		if (line[i] == '|' && !in_quote)
			line[i] = 31;
		i++;
	}
	if ((in_quote || has_unclosed_quotes(line)))
	{
		ft_putendl_fd("Syntax error: unclosed quotes", 2);
		shell->exit_status = 2;
		return (1);
	}
	return (0);
}

int	is_in_quotes(char c, int *in_single_quote, int *in_double_quote)
{
	if (c == '\'' && !(*in_double_quote))
	{
		*in_single_quote = !(*in_single_quote);
		return (*in_single_quote);
	}
	else if (c == '\"' && !(*in_single_quote))
	{
		*in_double_quote = !(*in_double_quote);
		return (*in_double_quote);
	}
	return (0);
}
