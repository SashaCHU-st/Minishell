/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permissions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:16:41 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/15 16:17:02 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	check_permissions(t_data *shell)
{
	int	i;
	i = 0;
	if (!shell || !shell->cmds || !shell->cmds->filenames || !shell->cmds->filetype)
	{
		ft_putendl_fd("Invalid shell or command structure", 2);
		shell->exit_status = 1;
		return (1);
	}
	while (shell->cmds->filenames[i])
	{
		if (access(shell->cmds->filenames[i], F_OK) != 0)
		{
			ft_putendl_fd("zsh: permission denied: no file path", 2);
			shell->exit_status = 1;
			return (1);
		}
		if (shell->cmds->filetype[i] == IN || shell->cmds->filetype[i] == HERE)
		{
			if (access(shell->cmds->filenames[i], R_OK) != 0)
			{
				ft_putendl_fd("zsh: permission denied: file is not readable", 2);
				shell->exit_status = 1;
				return (1);
			}
		}
		else if (shell->cmds->filetype[i] == OUT || shell->cmds->filetype[i] == APPEND)
		{
			if (access(shell->cmds->filenames[i], W_OK) != 0)
			{
				ft_putendl_fd("zsh: permission denied: file is not writable", 2);
				shell->exit_status = 1;
				return (1);
			}
		}
		i++;
	}
	return (0);
}