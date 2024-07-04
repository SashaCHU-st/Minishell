/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:45:33 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/04 16:34:39 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"
///!!!!!!!!!!!! roverka na to chto est' v export a ne v envp
int	is_var_in_envp(char *arg, t_data *data)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strchr(arg, '=') - arg;
	while (data->envp[i] != NULL)
	{
		if (ft_strncmp(data->envp[i], arg, len) == 0)
			return (i);
		else if (ft_strncmp(data->envp[i], arg, len) == 0 && data->envp[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	if_error_input(char *input_copy)
{
	if (input_copy == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
}
