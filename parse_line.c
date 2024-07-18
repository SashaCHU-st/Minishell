/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:12:53 by epolkhov          #+#    #+#             */
/*   Updated: 2024/07/16 12:25:01 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cmd_and_redir(t_data *shell)
{
	int	i;

	shell->cmds = (t_cmd *)malloc(sizeof(t_cmd) * shell->cmds_count);
	if (!shell->cmds)
		error_message(shell, "Failed to allocate memory", 1);
	i = -1;
	while (++i < shell->cmds_count)
		init_cmd(&shell->cmds[i]);
	make_redirs(shell);
	remove_redir_from_input(shell);
}

static void	cmd_and_expand(t_data *shell)
{
	int	i;
	int	j;

	i = -1;
	while (shell->pipe_tok[++i] && i < shell->cmds_count)
		shell->pipe_tok[i] = expand_var(shell, shell->pipe_tok[i]);
	i = 0;
	while (i < shell->cmds_count)
	{
		j = 0;
		while (shell->cmds[i].filenames[j])
		{
			shell->cmds[i].filenames[j] = expand_var(shell, \
								shell->cmds[i].filenames[j]);
			if (!shell->cmds[i].filenames[j])
				error_message(shell, 
				"Variable expansion failed in filenames", 1);
			j++;
		}
		i++;
	}
}

static t_cmd	split_into_wtok(char *pipe_token, t_cmd cmd)
{
	change_space_to_31(pipe_token);
	remove_quotes(pipe_token);
	cmd.word_tok = do_split(pipe_token, 31);
	if (!cmd.word_tok)
		return (cmd);
	while (cmd.word_tok[cmd.w_count])
		cmd.w_count++;
	return (cmd);
}

void	split_line(char *line, t_data *shell)
{
	int		i;

	shell->cmds_count = 0;
	is_heredoc(line, shell);
	shell->pipe_tok = do_split(line, 31);
	if (!shell->pipe_tok)
		return ;
	if (shell->pipe_tok)
	{
		while (shell->pipe_tok[shell->cmds_count])
			shell->cmds_count++;
	}
	cmd_and_redir(shell);
	cmd_and_expand(shell);
	i = -1;
	while (++i < shell->cmds_count)
		shell->cmds[i] = split_into_wtok(shell->pipe_tok[i], shell->cmds[i]);
}
