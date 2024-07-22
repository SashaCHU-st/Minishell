/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:56:28 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/22 15:18:22 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void	unset_var(t_data *sh, char *arg)
{
	int	i;
	int	j;
	int	len;

	len = ft_strlen(arg);
	i = 0;
	while (sh->envp[i] != NULL)
	{
		if (ft_strncmp(sh->envp[i], arg, len) == 0 && sh->envp[i][len] == '=')
			break ;
		i++;
	}
	if (sh->envp[i] == NULL)
	{
		printf("Environment variable %s not found.\n", arg);
		return ;
	}
	free(sh->envp[i]);
	j = i;
	while (sh->envp[j + 1] != NULL)
	{
		sh->envp[j] = sh->envp[j + 1];
		j++;
	}
	sh->envp[j] = NULL;
}
