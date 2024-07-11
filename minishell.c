/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:52:26 by epolkhov          #+#    #+#             */
/*   Updated: 2024/07/11 10:31:29 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

t_cmd	split_into_wtok(char *pipe_token, t_cmd cmd)
{

	//t_cmd	cmd;

	// cmd->word_tok = NULL;
	//cmd.w_count = 0;/// CHECK LATER
	change_space_to_31(pipe_token);
	remove_quotes(pipe_token);
	cmd.word_tok = do_split(pipe_token, 31);
	if (!cmd.word_tok)
		return (cmd);
	while (cmd.word_tok[cmd.w_count])
		cmd.w_count++;
	return (cmd);
}

void init_cmd(t_cmd *cmd)
{
	if (cmd == NULL)
		return;

	cmd->filenames = NULL;
	cmd->filetype = NULL;
	cmd->number_of_redir = 0;
	cmd->w_count = 0;
	cmd->word_tok = NULL;
}

void	split_line(char *line, t_data *shell)
{
	int		i;

shell->cmds_count =0;// CHECK THIS
	printf("input after replacing pipe: %s\n", line);
	is_heredoc(line, shell);

	shell->pipe_tok = do_split(line, 31);
	if (!shell->pipe_tok)
		return ;
	if (shell->pipe_tok)
	{
		while (shell->pipe_tok[shell->cmds_count])
			shell->cmds_count++;

	}
	printf("Total comand count: %d\n", shell->cmds_count);
	shell->cmds = (t_cmd *)malloc(sizeof(t_cmd) * shell->cmds_count);
	if (!shell->cmds)
		error_message(shell, "Failed to allocate memory", 1);
	i = -1;
	while (++i < shell->cmds_count)
		init_cmd(&shell->cmds[i]);
	make_redirs(shell);
	remove_redir_from_input(shell);
	i = -1;
	while (shell->pipe_tok[++i] && i < shell->cmds_count)
	{
		shell->pipe_tok[i] = expand_var(shell, shell->pipe_tok[i]);
		printf("Expand pipe tok: %s\n", shell->pipe_tok[i]);
		//i++;
	}
	printf("I am here\n");
	i = 0;
    while (i < shell->cmds_count) {
        int j = 0;
        while (shell->cmds[i].filenames[j])
		{


            shell->cmds[i].filenames[j] = expand_var(shell, shell->cmds[i].filenames[j]);
			printf("Expand filename %d: %s\n", j, shell->cmds[i].filenames[j]);
            if (!shell->cmds[i].filenames[j])
			{
                ft_putendl_fd("Variable expansion failed in filenames", 2);
                exit(EXIT_FAILURE);
            }
            j++;
        }
		i++;
    }

	for (int j = 0; j < shell->cmds_count; j++)
	{
		printf("Token after redir remove %d: %s\n", j, shell->pipe_tok[j]);
    }
	i = 0;
	while (i < shell->cmds_count)
	{
		shell->cmds[i] = split_into_wtok(shell->pipe_tok[i], shell->cmds[i]);

		if (shell->cmds[i].word_tok[0] != NULL)
		{
			if (ft_strncmp (shell->cmds[i].word_tok[0], "exit", 5) == 0)
				ft_exit(shell, shell->cmds[i].word_tok);
		}
		
		i++;
	}
	printf("Number of shell: %d\n", shell->cmds_count);
	for (int j = 0; j < shell->cmds_count; j++)
	{
		printf("Token %d: %s\n", j, shell->pipe_tok[j]);
	}
	for (i = 0; i < shell->cmds_count; i++) {
		printf("Command %d:\n", i);
		
		for (int j = 0; j < shell->cmds[i].w_count; j++) {
			printf("  Word %d: %s\n", j, shell->cmds[i].word_tok[j]);
		}
	}
 int if_builtins(t_data *data, t_cmd *cmd)
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

char	*read_line(t_data *line)
{
	char	*input;

	(void)line;
	input = readline("minishell-$ ");
	if (!input)
	{
		printf("exit\n");
		exit (EXIT_SUCCESS);
	}
	add_history(input);
	printf("input: %s\n", input);
	return (input);
}

void shell_loop(t_data *shell)
{
	char	*line;
	t_pipex	pipex;
	int i;
	
	while (1)
	{
		line = read_line(shell);
		if (input_validation_pipes(line) == 0 && input_validation_redir(line) == 0 \
					&& check_input_quotes_pipe(line) == 0)

		{
			line = change_to_space(line);
			split_line(line, shell);
			if (shell->cmds_count > 0)
			{
				i =0;
				while (i < shell->cmds_count)
				{
					if (if_builtins(shell, &shell->cmds[i]) == 1)
					{
						i++;
						continue;
					}
					else if (shell->cmds_count >=1 && if_builtins(shell, &shell->cmds[i]) == 0)
					{

					checking_path(shell, &pipex, i);
					piping(shell);
					forking(shell, pipex);
					closing(shell);
					}
				i++;

				}
			free(shell->cmds);
			}
		}
		free(line);
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

void init_t_data(t_data *data)
{
	data->envp= NULL;
	data->new_envp = NULL;
	data->pwd_index = 0;
	data->oldpwd_index = 0;
	data->input_copy = NULL;
	data->pipe_tok = NULL;
	data->cmds_count = 0;
	data->cmds = NULL;
	data->hd_delimeter = NULL;
	data->hd_count = 0;
	data->tempfile_hd = NULL;
	data->exit_status = 0;
}

int	main(int argc, char **argv, char *envp[])
{
	t_data data;

	init_t_data(&data);
	(void)argv;
	data.envp = copy_envp(envp);
	if(argc < 2)
	{
		if (isatty(STDIN_FILENO))
		{
			get_signal(HANDLER);
			shell_loop(&data);
		}
		else
		{
			perror("Terminal is not in interactive mode");
			return (EXIT_FAILURE);
		}
		return (EXIT_SUCCESS);
	}
}
