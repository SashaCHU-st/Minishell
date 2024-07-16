/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permission.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:02:23 by epolkhov          #+#    #+#             */
/*   Updated: 2024/07/16 12:30:47 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void write_msg_status(t_data *shell, char *msg, int status)
{
	ft_putendl_fd(msg, 2);
	shell->exit_status = status;
}

int	see_permission(t_data *shell, t_cmd *cmd, int i)
{
	// if (access(cmd->filenames[i], F_OK) != 0)
	// {
	// 	write_msg_status(shell, "zsh: permission denied: no file path", 1);
	// 	return (1);
	// }
	if (cmd->filetype[i] == IN || cmd->filetype[i] == HERE)
	{
		dprintf(2, "i am in permisiion IN\n");
		printf("check file in: %s\n",  cmd->filenames[i]);
		if (access(cmd->filenames[i], R_OK) != 0)
		{
			write_msg_status(shell, "zsh: permission denied: file is not readable", 1);
			return (1);
		}
	}
	else if (cmd->filetype[i] == OUT || cmd->filetype[i] == APPEND)
	{
		dprintf(2, "i am in permisiion OUT begin\n");
		printf("check file out: %s\n",  cmd->filenames[i]);
		if (access(cmd->filenames[i], W_OK) != 0)
		{
			dprintf(2, "i am in permisiion OUT\n");
			write_msg_status(shell, "zsh: permission denied: file is not writable", 1);
			return (1);
		}
	}
	return(0);
}

int	check_permissions(t_data *shell)
{
	int	j;
	j  = 0;
	if (shell->cmds->filenames[j] ==  NULL)
		return (0);
	else
	{
			
			while (shell->cmds->filenames[j])
			{
				if (see_permission(shell, shell->cmds, j) == 1)
				{
					//f_free_cmds(shell->cmds, shell->cmds_count);
					return (1);
				}
					j++;
			}
	}
	return (0);
}
