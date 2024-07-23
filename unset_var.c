/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:56:28 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/22 21:03:45 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

static void	shift_env_vars(t_data *data, int index)
{
	int	j;

	j = index;
	free(data->envp[index]);
	while (data->envp[j + 1] != NULL)
	{
		data->envp[j] = data->envp[j + 1];
		j++;
	}
	data->envp[index] = NULL;
}

void	unset_var(t_data *data, char *arg)
{
	int	i;
	//int	j;
	int	len;

	len = ft_strlen(arg);
	i = 0;
	while (data->envp[i] != NULL)
	{
		if (ft_strncmp(data->envp[i], arg, len) == 0 && \
			data->envp[i][len] == '=')
			break ;
		i++;
	}
	if (data->envp[i] == NULL)
	{
		printf("Environment variable %s not found.\n", arg);
		return ;
	}
	shift_env_vars(data, i);
	//free(data->envp[i]);
	// j = i;
	// while (data->envp[j + 1] != NULL)
	// {
	// 	data->envp[j] = data->envp[j + 1];
	// 	j++;
	// }
	// data->envp[j] = NULL;
}
