/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:30:19 by epolkhov          #+#    #+#             */
/*   Updated: 2024/07/18 18:20:01 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_cmd(t_cmd *cmd)
{
	if (cmd == NULL)
		return ;
	cmd->filenames = NULL;
	cmd->filetype = NULL;
	cmd->number_of_redir = 0;
	cmd->w_count = 0;
	cmd->word_tok = NULL;
}

void	init_t_data(t_data *data)
{
	data->envp = NULL;
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
	data->pipe_count = 0;
	data->var_name_len = 0;
	data->envp_size = 0;
	data->var_len = 0;
	data->in_dquotes = 0;
	data->filename = NULL;
	data->in_single_quote = 0;
	data->in_double_quote = 0;
	data->in_quotes = 0;
	data->new_line = NULL;
	data->line = NULL;
	data->hd_index = 0;
	memset(data->pwd, 0, sizeof(data->pwd));
	data->redir_count = 0;
	data->pipe = NULL;
	data->parent_out = 0;
	data->parent_in = 0;
	data->pid = NULL;
	data->path = NULL;
	data->expanded_line = NULL;
}
