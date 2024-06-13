/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:52:26 by epolkhov          #+#    #+#             */
/*   Updated: 2024/06/13 10:41:43 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void	check_input_quotes_pipe(char *line)
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
		error_message("Syntax error: unclosed quotes");
}

//void	is_heredoc(char *line)
//{
//	int		i;
//	char	*str_delimeter;
//	int		j;

//	str_delimeter = NULL;
//	i = 0;
//	while (ft_strncmp(&line[i], "<<", 2) != 0)
//		i++;
//	i = i + 2;
//	while (check_space(line[i]))
//		i++;
//	j = 0;
//	while (line[i] && line[i] != 31 && !check_space(line[i]))
//	{
//		str_delimeter = realloc(str_delimeter, (j + 2) * sizeof(char));
//		if (str_delimeter == NULL)
//			error_message("Memory allocation error\n");
//		str_delimeter[j++] = line[i++];
//	}
//	str_delimeter[j] = '\0';
//	printf("delimeter Heredoc:%s\n", str_delimeter);
//	free(str_delimeter);
//}

t_tok	split_line(char *line)
{
	t_tok	tokens;

	tokens.pipe_tok = NULL;
	tokens.size = 0;
	input_validation_pipes(line);
	input_validation_redir(line);
	check_input_quotes_pipe(line);
	printf("input after replacing pipe: %s\n", line);
	//is_heredoc(line);
	tokens.pipe_tok = do_split(line, 31);
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

char	*read_line(t_built *data)
{
	char	*input;

	input = readline("minishell-$ ");
	int number_of_inputs = 0;
	if (!input)
		error_message("Failed to read line");
	/////////////////
	data->inputs = do_split(input, 32);
	while (data->inputs[number_of_inputs])
			number_of_inputs++; 
   // printf("!!!!!!!!!! %d\n", number_of_inputs); 
	
	if( number_of_inputs > 0)
	{
	if (ft_strncmp(data->inputs[0], "pwd", 4) == 0)
		ft_pwd();
	else if(ft_strncmp(data->inputs[0], "echo", 5) == 0) //if found echo, nujno esche $ pro env
		ft_echo(data, number_of_inputs);
	else if(ft_strncmp(data->inputs[0], "env", 4) == 0)
		ft_env(data);
	else if(ft_strncmp(data->inputs[0], "export", 7) == 0)
		ft_export(data, number_of_inputs);
	else if (ft_strncmp(data->inputs[0], "cd", 3) == 0)//// DOES NOT REALLY WORKS!!!!!!!
		ft_cd(data, number_of_inputs);
	else if(ft_strncmp(data->inputs[0], "unset", 6) == 0)
		ft_unset(data, number_of_inputs);
	///////////////////////////
	else if (strcmp(data->inputs[0], "exit") == 0)
	{
		free(input);
		printf ("exit\n");
		exit(EXIT_SUCCESS);
	}
	}
	add_history(input);
	printf("input: %s\n", input);
	return (input);
}

void	shell_loop(t_built *data)
{
	char	*line;
	t_tok	pipe_tok_str;
	
	(void)pipe_tok_str;
	while (1)
	{
		line = read_line(data);
		pipe_tok_str = split_line(line);
		free (line);
	}
}
char **copy_envp(char *envp[])
{
	int count = 0;
	while (envp[count] != NULL)
		count++;
	char **new_envp = malloc((count + 1) * sizeof(char *));
	if (new_envp == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	int i = 0;
	while ( i < count)
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (new_envp[i] == NULL)
		{
			perror("strdup");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	new_envp[count] = NULL;
	return(new_envp);
}
int	main(int argc, char **argv, char *envp[])
{
	t_built data;
	(void)argv;
	data.envp = copy_envp(envp);
	if(argc < 2)
	{
		if (isatty(STDIN_FILENO))
			shell_loop(&data);
		else
		{
			perror("Terminal is not in interactive mode");
			return (EXIT_FAILURE);
		}
		return (EXIT_SUCCESS);
	}
}
