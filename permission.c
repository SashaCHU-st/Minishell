/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permission.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-15 18:02:23 by epolkhov          #+#    #+#             */
/*   Updated: 2024-07-15 18:02:23 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void write_msg_status(t_data *shell, char *msg, int status)
{
	ft_putendl_fd(msg, 2);
	shell->exit_status = status;
}

int	see_permission(t_data *shell, int i)
{
	if (access(shell->cmds->filenames[i], F_OK) != 0)
	{
		write_msg_status(shell, "zsh: permission denied: no file path", 1);
		return (1);
	}
	if (shell->cmds->filetype[i] == IN || shell->cmds->filetype[i] == HERE)
	{
		if (access(shell->cmds->filenames[i], R_OK) != 0)
		{
			write_msg_status(shell, "zsh: permission denied: file is not readable", 1);
			return (1);
		}
	}
	else if (shell->cmds->filetype[i] == OUT || shell->cmds->filetype[i] == APPEND)
	{
		if (access(shell->cmds->filenames[i], W_OK) != 0)
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

	i = 0;
	if (!shell || !shell->cmds || !shell->cmds->filenames || !shell->cmds->filetype)
	{
		write_msg_status(shell, "Invalid shell or command structure", 1);
		return (1);
	}
	while (shell->cmds->filenames[i])
	{
		if (see_permission(shell, i) == 1)
			return (1);
		i++;
	}
	return (0);
}
