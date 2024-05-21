/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newmain.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:52:26 by epolkhov          #+#    #+#             */
/*   Updated: 2024/05/21 09:24:37 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;

	if (!s)
		return (NULL);
	if (start > strlen(s))
	{
		substr = malloc(1);
		if (!substr)
			return (NULL);
		substr[0] = '\0';
		return (substr);
	}
	if (len > strlen(s) - start)
		len = strlen(s) - start;
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (substr == NULL)
		return (NULL);
	strlcpy(substr, s + start, len + 1);
	return (substr);
}

static unsigned int	num_of_str(const char *s, char c)
{
	unsigned int	count;
	int				in_field;

	if (!s)
		return (0);
	count = 0;
	in_field = 0;
	while (*s)
	{
		if (*s == c)
		{
			if (in_field)
				in_field = 0;
		}
		else
		{
			if (!in_field)
			{
				in_field = 1;
				count++;
			}
		}
		s++;
	}
	return (count);
}

// Function to free memory allocated for an array of strings
static void	f_free_array(char **r)
{
	char	**ptr;

	if (!r)
		return ;
	ptr = r;
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(r);
}

static char	**f_fill_array(char const *s, char c, unsigned int nb)
{
	char			**array;
	unsigned int	start;
	unsigned int	i;
	unsigned int	len;

	if (!s)
		return (NULL);
	array = (char **)malloc((nb + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	start = 0;
	i = 0;
	while (i < nb)
	{
		if (s[start] != c)
		{
			len = 0;
			while (s[start + len] != c && s[start + len] != '\0')
				len++;
			array[i] = ft_substr(s, start, len);
			if (!array[i])
			{
				f_free_array(array);
				return (NULL);
			}
			i++;
			start += len;
		}
		else
			start++;
	}
	array[i] = NULL;
	return (array);
}

// Function to split a string into an array of substrings based on a delimiter character
char	**ft_split(char const *s, char c)
{
	unsigned int	n_of_substr;

	if (!s)
		return (NULL);
	n_of_substr = num_of_str(s, c);
	return (f_fill_array(s, c, n_of_substr));
}

bool	has_unclosed_quotes(char *line)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			count++;
		i++;
	}
	if (count % 2 == 0)
		return (false);
	return (true);
}

t_tok	split_line(char *line)
{
	t_tok	tokens;
	int		i;
	int		in_quote;

	tokens.pipe_tok = NULL;
	tokens.size = 0;
	in_quote = 0;
	i = 0;
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
		perror("Unclosed quotes");
		exit(1);
	}
	tokens.pipe_tok = ft_split(line, 31);
	if (tokens.pipe_tok)
	{
		while (tokens.pipe_tok[tokens.size])
			tokens.size++;
	}
	printf("Number of tokens: %d\n", tokens.size);
	for (int j = 0; j < tokens.size; j++)
    {
        printf("Token %d: %s\n", j, tokens.pipe_tok[j]);
    }
	return (tokens);
}

char	*read_line(void)
{
	char	*input;

	input = readline("minishell-$ ");
	if (!input)
	{
		perror("Failed to read line");
		exit(EXIT_FAILURE);
	}
	else if (strcmp(input, "exit") == 0)
	{
		free(input);
		printf ("exit\n");
		exit(EXIT_SUCCESS);
	}
	add_history(input);
	printf("input: %s\n", input);
	return (input);
}

void shell_loop(void)
{
	char	*line;
	t_tok	pipe_tok_str;

	while (1)
	{
		line = read_line();
		pipe_tok_str = split_line(line);
		free (line);
	}
}

int	main()
{
	if (isatty(STDIN_FILENO))
		shell_loop();
	else
	{
		perror("Terminal is not in interactive mode");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}