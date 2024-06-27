/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:52:26 by epolkhov          #+#    #+#             */
/*   Updated: 2024/06/26 13:33:35 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

t_cmd	split_into_wtok(char *pipe_token)
{
	t_cmd	cmd;
	int		i;
	int		j;
	char	**words;
	t_cmd	new_words;

	cmd.word_tok = NULL;
	cmd.w_count = 0;
	i = 0;
	change_space_to_31(pipe_token);
	remove_quotes(pipe_token);
	words = do_split(pipe_token, 31);
	if (!words)
	{
		cmd.word_tok = NULL;
        cmd.w_count = 0;
		f_free_array(words);
		return (cmd);
	}
	while (words[i])
	{
		new_words.word_tok = malloc(sizeof(char *) * (cmd.w_count + 1));
		if (!new_words.word_tok)
			error_message("Failed to allocate memory");
		j = 0;
		while (j < cmd.w_count)
		{
			new_words.word_tok[j] = cmd.word_tok[j];
			j++;
		}
		new_words.word_tok[cmd.w_count] = ft_strdup(words[i]);
		if (!new_words.word_tok[cmd.w_count])
			error_message("Failed to duplicate string");
		free (cmd.word_tok);
		cmd.word_tok = new_words.word_tok;
		cmd.w_count++;
		i++;
	}
	f_free_array(words);
	return (cmd);
}


e_filetype peek(char *line, int index)
{
    if (line[index] == '<' && line[index + 1] == '<') 
		return (HERE);
    if (line[index] == '<')
		return (IN);
    if (line[index] == '>' && line[index + 1] == '>')
		return (APPEND);
    if (line[index] == '>')
		return (OUT);
    return (NONE);
}

char *ft_strndup(const char *str, size_t n)
{
    size_t len;
    size_t i;
	char *dup;

    len =  0;
	i = 0;
	while (str[i] && len < n)
	{
        len++;
        i++;
    }
   	dup = (char *)malloc(len + 1);
    if (!dup)
        return (NULL);
    i = 0;
    while (i < len)
	{
        dup[i] = str[i];
        i++;
    }
    dup[i] = '\0';
    return (dup);
}

char *take_filename(char *line, int *index)
{
    int		start;
	char	*filename;

	while (check_space(line[*index]))
		(*index)++;
    start = *index;
    while (line[*index] && !check_space(line[*index]) && line[*index] != '<' && \
			 line[*index] != '>' && line[*index] != 31)
		(*index)++;
	filename = ft_strndup(&line[start], *index - start);
    return (filename);
}

void make_redirs(t_data *tokens)
{
	int			i;
	int			j;
	char		*line;
	e_filetype	type;
	int			redir_count;
	char		*filename;

	i = -1;
	while (tokens->pipe_tok[++i] &&  i < tokens->cmds_count)
	{
		j = 0;
		line = tokens->pipe_tok[i];
		redir_count = 0;
		tokens->cmds[i].filenames = malloc(sizeof(char *) * (MAX_REDIRECTIONS + 1));
        tokens->cmds[i].filetype = malloc(sizeof(int) * (MAX_REDIRECTIONS + 1));
		if (!tokens->cmds[i].filenames || !tokens->cmds[i].filetype)
           error_message("Memory allocation error");
		while (line[j] && redir_count <  MAX_REDIRECTIONS)
		{
			type = peek(line, j);
			printf("Type: %d\n", type);
			if (type != NONE)
			{
				
				if (type == HERE || type == APPEND)
					j += 2;
				else
					j++;
				while (check_space(line[j]))
					j++;
				
				filename = take_filename(line, &j);
				printf("Filename: %s\n", filename);
				if (filename)
				{
					if (type == HERE)
					{
						tokens->cmds[i].filenames[redir_count] = tokens->tempfile_hd;
					}
					else
						tokens->cmds[i].filenames[redir_count] = filename;
					printf("Array filename: %s\n", tokens->cmds[i].filenames[redir_count]);
					tokens->cmds[i].filetype[redir_count] = type;
					printf("FILEtype %d\n", tokens->cmds[i].filetype[redir_count]);
					printf("Redir count: %d\n",  redir_count);
					redir_count++;
				}
				else
					ft_putendl_fd("Syntax error: no filename", 2);
			}
			else
				j++;

		}
		tokens->cmds[i].filenames[redir_count] = NULL;
        tokens->cmds[i].filetype[redir_count] = NONE;
        tokens->cmds[i].number_of_redir = redir_count;
		printf("Redir count: %d\n",  tokens->cmds[i].number_of_redir);
	}
}

void	remove_redir_from_input(t_data *tokens)
{
	char	*line;
	char	*new_line;
	int		i;
	int		j;
	int		k;

	i = -1;
	while (tokens->pipe_tok[++i] &&  i < tokens->cmds_count)
	{
		line = tokens->pipe_tok[i];
		new_line = (char *)malloc(sizeof(char) * (ft_strlen(line) + 1));
		if (!new_line)
			error_message("Failed to malloc for newline");
		j = 0;
		k = 0;
		while (line[j])
		{
			if ((line[j] == '<' || line[j] == '>' ))
			{
				if ((line[j] == '<' && line[j + 1] == '<' ) || (line[j] == '>' && line[j + 1] == '>'))
					j += 2;
				else
					j++;
				while (check_space(line[j]))
					j++;
				while (line[j] && line[j] != '<' && \
						line[j] != '>' && line[j] != 31 && line[j] != ' ')
					j++;
			}
			new_line[k] = line[j];
			j++;
			k++;	
		}
		new_line[k] = '\0';
		tokens->pipe_tok[i] = new_line;
		free(line);
		//free(new_line);
	}
}

void	init_t_data(t_data *tokens)
{
	tokens->pipe_tok = NULL;
	tokens->cmds_count = 0;
	tokens->cmds = NULL;
}

t_data	split_line(char *line)
{
	t_data	tokens;
	int		i;

	// tokens.pipe_tok = NULL;
	// tokens.cmds_count = 0;
	// tokens.cmds = NULL;
	init_t_data(&tokens);
	printf("input after replacing pipe: %s\n", line);
	is_heredoc(line, &tokens); // is_heredoc(line, t_data *tokens);
	tokens.pipe_tok = do_split(line, 31);
	if (!tokens.pipe_tok)
		return (tokens);
	if (tokens.pipe_tok)
	{
		while (tokens.pipe_tok[tokens.cmds_count])
			tokens.cmds_count++;
	}
	//void make_redirs(t_data *tokens)
	//?? expand $VAR  in tokens.pipe_tok  and in tokens->cmds->filenames.
	tokens.cmds = (t_cmd *)malloc(sizeof(t_cmd) * tokens.cmds_count);
	if (!tokens.cmds)
		error_message("Failed to allocate memory");
	i = 0;
	while (i < tokens.cmds_count)
	{
		tokens.cmds[i].filenames = NULL;
        tokens.cmds[i].filetype = NULL;
		//tokens.cmds[i].number_of_redir = 0;
		i++;
	}
	make_redirs(&tokens);
	remove_redir_from_input(&tokens);
	for (int j = 0; j < tokens.cmds_count; j++)
    {
        printf("Token after redir remove %d: %s\n", j, tokens.pipe_tok[j]);
    }
	i = 0;
	while (i < tokens.cmds_count)
	{
		
		tokens.cmds[i] = split_into_wtok(tokens.pipe_tok[i]);
		i++;
	}


	printf("Number of tokens: %d\n", tokens.cmds_count);
	for (int j = 0; j < tokens.cmds_count; j++)
    {
        printf("Token %d: %s\n", j, tokens.pipe_tok[j]);
    }
	
	for (i = 0; i < tokens.cmds_count; i++) {
        printf("Command %d:\n", i);
		
        for (int j = 0; j < tokens.cmds[i].w_count; j++) {
            printf("  Word %d: %s\n", j, tokens.cmds[i].word_tok[j]);
        }
		
    }
	
	// for (i = 0; i < tokens.cmds_count; i++) {
    //     for (int j = 0; j < tokens.cmds[i].w_count; j++) {
    //         free(tokens.cmds[i].word_tok[j]);
    //     }
    //     free(tokens.cmds[i].word_tok);
    // }
    // free(tokens.cmds);
    // f_free_array(tokens.pipe_tok);
	return (tokens);
}

 int if_builtins(t_built *data, t_cmd *cmd)
{
	if (ft_strncmp(cmd->word_tok[0], "pwd", 4) == 0)
			ft_pwd();
	else if (ft_strncmp(cmd->word_tok[0], "echo", 5) == 0)
			ft_echo(data, cmd->w_count);
	else if (ft_strncmp(cmd->word_tok[0], "env", 4) == 0)
		ft_env(data);
	else if (ft_strncmp(cmd->word_tok[0], "export", 7) == 0)
		ft_export(data, cmd->w_count);
	else if (ft_strncmp(cmd->word_tok[0], "cd", 3) == 0)
		ft_cd(data, cmd->w_count);
	else if (ft_strncmp(cmd->word_tok[0], "unset", 6) == 0)
			ft_unset(data, cmd->w_count);
	else
		return(0);
	return(1);
}

char	*read_line(t_built *line)
{
	char	*input;

	(void)line;
	input = readline("minishell-$ ");
	if (!input)
		error_message("Failed to read line");

	if (ft_strncmp(input, "exit", 5) == 0)
	{
		free(input);
		printf ("exit\n");
		exit(EXIT_SUCCESS);
	}
	add_history(input);
	printf("input: %s\n", input);
	return (input);
}

void	shell_loop(t_built *shell)
{
	char	*line;
	int		i;

	t_pipex	pipex;
	char	*path;

	i = 0;
	while (1)
	{
		line = read_line(shell);
		if (input_validation_pipes(line) == 0 && input_validation_redir(line) == 0 \
					&& check_input_quotes_pipe(line) == 0)
		{
			line = change_to_space(line);
			shell->data = split_line(line);
		}
	
		if (shell->data.cmds_count > 0)
        {
            i = 0;
            while (i < shell->data.cmds_count)
            {
                if (if_builtins(shell, &shell->data.cmds[i]) == 1)
                {
                    i++;
                    continue;
                }
                else if (shell->data.cmds->w_count == 4 && if_builtins(shell, &shell->data.cmds[i]) == 0)
                {
                	path = mine_path(shell);
                    if (path)
                        printf("%s\n", path);
                    else
                        printf("KUKUUUUUUU\n");
                    if (pipe(pipex.fd) == -1)
                    {
                        perror("Error in pipe()");
                        exit(1);
                    }
                    pipex.commands_path = ft_split(path, ':');
                    if (pipex.commands_path == NULL)
                    {
                        close(pipex.fd[0]);
                        close(pipex.fd[1]);
                        free_fun(&pipex);
                        i++;
                    }
                    creating_children(&pipex, shell, shell->data.cmds->w_count);
                    close(pipex.fd_in);
                    close(pipex.fd_out);
                }
                else 
                    printf("HELLO_WORLD\n");
                i++;
            }
            free(shell->data.cmds);
        }
		// for (int i = 0; i < shell->data.cmds_count; i++) {
        //     f_free_array(shell->data.cmds[i].word_tok);
        // }
        // free(shell->data.cmds);
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
