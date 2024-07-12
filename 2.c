void shell_loop(t_data *shell)
{
	char	*line;
	t_pipex	pipex;
	int i = 0;
	
	while (1)
	{
		line = read_line(shell);
		if (input_validation_pipes(shell, line) == 0 && input_validation_redir(shell, line) == 0 \
					&& check_input_quotes_pipe(shell,line) == 0)

		{
			line = change_to_space(line);
			split_line(line, shell);
			if (shell->cmds_count > 0)
			{
				i =0;
				checking_path(shell, &pipex, i);
				//printf("cmds[i] %s\n",&shell->cmds[i]);
				printf("if_it_is_builtins( &shell->cmds[i]) %d\n", if_it_is_builtins( &shell->cmds[i]));
				if (if_it_is_builtins( &shell->cmds[i]) == 1)
				{
					printf("HELLO");
					if (shell->cmds->filetype[i] == NONE)
						builtins(shell, &shell->cmds[i]);
					if (shell->cmds[i].number_of_redir > 0)
					{
						if(shell->cmds->filetype[i] == OUT)
						{
							shell->parent_out= dup(STDOUT_FILENO);
							open_fd_out(&pipex, *shell->cmds->filenames);
							check_filetype(&pipex,&shell->cmds[i]);
							builtins(shell, &shell->cmds[i]);
							if (dup2(shell->parent_out, STDOUT_FILENO)  < 0)
								dprintf(2, "dup2 \n");
							close(shell->parent_out);
						}
						if(shell->cmds->filetype[i] == IN)
						{
							shell->parent_in= dup(STDIN_FILENO);
							check_filetype(&pipex,&shell->cmds[i]);
							if (dup2(shell->parent_in, STDIN_FILENO)  < 0)
								dprintf(2, "dup2 \n");
							close(shell->parent_out);
						}
					}
				}
				else if (shell->cmds_count >=1 && if_it_is_builtins( &shell->cmds[i]) == 0)
				{
					piping(shell);
					forking(shell, pipex);
					closing(shell);
				}
				i++;
			free(shell->cmds);
			}
		}
		free(line);
	}
}