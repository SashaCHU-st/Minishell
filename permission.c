/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permission.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:02:23 by epolkhov          #+#    #+#             */
/*   Updated: 2024/07/16 14:22:41 by aheinane         ###   ########.fr       */
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
	printf("I am in perm \n");
	if (access(cmd->filenames[i], F_OK) != 0)
	{
		write_msg_status(shell, "zsh: permission denied: no file path", 1);
		return (1);
	}
	if (cmd->filetype[i] == IN || cmd->filetype[i] == HERE)
	{
		dprintf(2, "i am in permisiion IN\n");
		if (access(cmd->filenames[i], R_OK) != 0)
		{
			write_msg_status(shell, "zsh: permission denied: file is not readable", 1);
			return (1);
		}
	}
	else if (cmd->filetype[i] == OUT || cmd->filetype[i] == APPEND)
	{
		if (access(cmd->filenames[i], W_OK) != 0)
		{
			write_msg_status(shell, "zsh: permission denied: file is not writable", 1);
			return (1);
		}
	}
	return(0);
}

int	check_permissions(t_data *shell)
{
	int	i;
	int	j;

	i = 0;
	if (!shell || !shell->cmds)
	{
		printf("eeeeee\n");
		//write_msg_status(shell, "Invalid shell or command structure", 1);
		return (0);
	}
	while (shell->cmds[i].filenames)
	{
		j  = 0;
		while (shell->cmds[i].filenames[j])
		{
			if (see_permission(shell, &shell->cmds[i], j) == 1)
				return (1);
			else
				j++;
		}
		i++;
	}
	return (0);
}
