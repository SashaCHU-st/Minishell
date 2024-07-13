/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:30:19 by epolkhov          #+#    #+#             */
/*   Updated: 2024/07/13 12:24:40 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	data->hd_interrupt = 0;
	data->pipe_count = 0;
}
