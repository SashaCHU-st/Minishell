/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newmain.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:52:26 by epolkhov          #+#    #+#             */
/*   Updated: 2024/05/17 12:52:29 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	wordcount(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

static char	*wordtoprint(const char **s, char c)
{
	int			i;
	char		*word;
	const char	*str;

	str = *s;
	i = 0;
	while (*str && *str == c)
		str++;
	while (str[i] && str[i] != c)
		i++;
	word = malloc(sizeof(char) * (i + 1));
	if (word == NULL)
		return (NULL);
	i = 0;
	while (*str && *str != c)
	{
		word[i] = *str;
		i++;
		str++;
	}
	word[i] = '\0';
	*s = str;
	return (word);
}

static	void free_all(int i, char **ptr)
{
	while (i > 0)
	{
		free(ptr[i - 1]);
		i--;
	}
	free(ptr);
}

char	**ft_split(char const *s, char c)
{
	int		len;
	char	**newstr;
	int		i;

	if (!s)
		return (NULL);
	len = wordcount(s, c);
	newstr = (char **)malloc((len + 1) * sizeof(char *));
	if (newstr == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		newstr[i] = wordtoprint(&s, c);
		if (newstr[i] == NULL)
		{
			free_all(i, newstr);
			return (NULL);
		}
		i++;
	}
	newstr[i] = 0;
	return (newstr);
}

bool	isCommand(char *str)
{
	if (!strcmp(str, "echo -n") || !strcmp(str, "cd") || !strcmp(str, "pwd") || \
		!strcmp(str, "export") || !strcmp(str, "unset") || !strcmp(str, "env"))
		return (true);
	return (false);
}

bool	isRedirect(char *str)
{
	if (!strcmp(str, "<") || !strcmp(str, ">") || !strcmp(str, ">>") || \
        !strcmp(str, "<<"))
		return(true);
	return(false);
}

t_tok	split_line(char *line)
{
	t_tok	tokens;
	tokens.pipe_tok = NULL;
	tokens.size = 0;
	//char	**str_array;
	int		i;
	//int		size;

	//size = 64;
	i = 0;
	// str_array = malloc(size * sizeof(char*));
	// if (!str_array)
	// {
	// 	perror("Memory allocation failed");
	// 	exit(1);
	// }
	while (line[i])
	{
		if (line[i] == '|' && line[i - 1] != '"' && line[i - 1] != 39 && line[i + 1] != '"' && line[i + 1] != 39)
			line[i] = 31;
		i++;
	}
	tokens.pipe_tok = ft_split(line, 31);
	if (tokens.pipe_tok)
	{
		while (tokens.pipe_tok[tokens.size] != NULL)
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

	input = readline("");
	if (input != NULL)
	{
		if (strcmp(input, "exit") == 0)
		{
			free (input);
			printf ("exit");
			exit (EXIT_SUCCESS);
		}
		if (input != NULL)
		{
			add_history(input);
			printf("input: %s\n", input);
			free(input);
		}
	}
	else
	{
		perror("Failed to read line");
		exit(EXIT_FAILURE);
	}
	return (input);
}

void	shell_loop(void)
{
	char	*line;
	t_tok	tok_str;

	while (1)
	{
		printf("minishell-$ ");
		line = read_line();
		tok_str = split_line(line);
		// free(line);
        // free_all(tok_str.size, tok_str.pipe_tok);
	}
	
}

int	main()
{
	//char	cwd[1024];

	if(isatty (STDIN_FILENO))
	{
		// if ((getcwd(cwd, sizeof(cwd)) != NULL))
		// {
			//printf("%s", cwd);
			shell_loop();
		// }
		// else
		// {
		// 	perror("getcwd failed");
		// 	return(EXIT_FAILURE);
		// }
	}
	else
	{
		perror("Not a terminal");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
