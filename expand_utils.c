/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:07:05 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/23 18:54:51 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

char	*ft_getenv(t_data *shell, char *env)
{
	char	*new_env;
	int		i;
	int		len;

	i = -1;
	if (!env || !*env)
		return (NULL);
	len = ft_strlen(env);
	while (shell->envp[++i])
	{
		if (!ft_strncmp(shell->envp[i], env, len))
		{
			if (shell->envp[i][len] == '=')
			{
				new_env = ft_strdup(shell->envp[i] + len + 1);
				if (!new_env)
					error_message(shell, "Failed to malloc env", 1);
				return (new_env);
			}
		}
	}
	return (NULL);
}

int	end_character(char c)
{
	return (c == '\0' || c == ' ' || c == '$'
		|| c == '\"' || c == '\'' || c == '=' || c == ':');
}

char	*receive_exit_status(t_data *shell)
{
	char	*status;

	if (shell->exit_status > 255)
		status = ft_itoa(WEXITSTATUS(shell->exit_status));
	else
		status = ft_itoa(shell->exit_status);
	if (!status)
		error_message(shell, "Malloc failed", 1);
	return (status);
}

void	cmd_and_expand(t_data *shell)
{
	int	i;
	int	j;

	i = -1;
	while (shell->pipe_tok[++i] && i < shell->cmds_count)
	{
		dprintf(2,"before\n");
		shell->pipe_tok[i] = expand_var(shell, shell->pipe_tok[i]);
		dprintf(2,"after\n");
		if (!shell->pipe_tok[i])
			error_message(shell, "Failed to expand", 1);
	}
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
