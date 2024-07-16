/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:56:28 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/16 20:10:41 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void	unset_var(t_data *data, char *arg)
{
	int	i;
	int	j;
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
		printf(" ");
		return ;
	}
	j = i;
	while (data->envp[j] != NULL)
	{
		data->envp[j] = data->envp[j + 1];
		j++;
	}
}
