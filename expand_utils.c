/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:07:05 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/17 17:47:30 by aheinane         ###   ########.fr       */
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
