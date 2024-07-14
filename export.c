/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:35:40 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/04 16:35:01 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

void	checking_export(t_data *data)
{
	int		i;
	char	*kuku;

	i = 0;
	while (data->envp[i] != NULL)
	{
		if (data->envp[i][0] != '_')
		{
			kuku = ft_strchr(data->envp[i], '=');
			if (kuku != NULL)
				printf("declare -x %.*s=\"%s\"\n", (int)(kuku - data->envp[i]), data->envp[i], kuku + 1);
			else
				printf("declare -x %s\n", data->envp[i]);
			i++;
		}
		else
			i++;
	}
}

void	new_envp_size(t_data *data, int new, int i, char **new_envp)
{
	while (new < i)
	{
		new_envp[new] = data->envp[new];
		new++;
	}
}

void	not_in_var(t_data *data, char *input_copy, char *added_var)
{
	char	**new_envp;
	int		envp_size;
	int		new;

	new = 0;
	envp_size = 0;
	while (data->envp[envp_size] != NULL)
		envp_size++;
	new_envp = malloc((envp_size + 2) * sizeof(char *));
	if (new_envp == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	new_envp_size(data, new, envp_size, new_envp);
	added_var = ft_strdup(input_copy);
	if (added_var != NULL)
	{
		new_envp[envp_size] = added_var;
		new_envp[envp_size + 1] = NULL;
		free(data->envp);
		data->envp = new_envp;
	}
	else
		free(new_envp);
}

void	export_with(t_data *shell, int number_of_inputs)
{
	char	*added_var;
	char	*input_copy;
	int		j;
	int		var_index;

	j = 1;
	while (j < number_of_inputs)
	{
		input_copy = ft_strdup(shell->cmds->word_tok[j]);
		if_error_input(input_copy);
		if_quotes(input_copy);
		var_index = is_var_in_envp(input_copy, shell);
		if (var_index >= 0)
		{
			free(shell->envp[var_index]);
			added_var = ft_strdup(input_copy);
			if (added_var != NULL)
				shell->envp[var_index] = added_var;
		}
		else
			not_in_var(shell, input_copy, added_var);
		free(input_copy);
		j++;
	}
}

void	ft_export(t_data *data, int number_of_inputs)
{
	if (number_of_inputs > 1)
		export_with(data, number_of_inputs);
	else if (number_of_inputs == 1)
		checking_export(data);
}
