/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permission.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:02:23 by epolkhov          #+#    #+#             */
/*   Updated: 2024/07/16 18:16:07 by aheinane         ###   ########.fr       */
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

		if (access(cmd->filenames[i], R_OK) != 0)
		{
			write_msg_status(shell, "sashel: permission denied: file is not readable", 1);
			return (1);
		}
	}
	if (cmd->filetype[i] == OUT || cmd->filetype[i] == APPEND)
	{
		dprintf(2, "i am in permisiion OUT begin\n");
		if (access(cmd->filenames[i], W_OK) != 0)
		{
			write_msg_status(shell, "zsh: permission denied: file is not writable", 1);

			return (1);
		}
	}
	return(0);
}

int	check_permissions(t_data *shell, int k)
{
	int	j;
	

	j  = 0;
	if (shell->cmds->filenames[j] ==  NULL)
		return (0);
	else
	{
		while (shell->cmds[k].filenames[j])
		{
			//printf("filenames: %s\n",shell->cmds->filenames[j]);
			if (see_permission(shell, &shell->cmds[k], j) == 1)
				return (1);
			j++;
			//printf("filenames: %s\n",shell->cmds->filenames[j]);
		}
	}
	return (0);
}
