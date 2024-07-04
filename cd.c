/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:39:27 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/04 16:32:12 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"
#include "structs.h"

void	update_pwd(t_data *data, char *original)
{
	char	*new_pwd;
	char	*pwd_value;
	char	*old_pwd;

	if (data->envp[data->pwd_index] != NULL)
	{
		free(data->envp[data->pwd_index]);
		pwd_value = getcwd(NULL, 0);
		if (pwd_value != NULL)
		{
			new_pwd = ft_strjoin("PWD=", pwd_value);
			if (new_pwd != NULL)
			{
				data->envp[data->pwd_index] = ft_strdup(new_pwd);
				free(new_pwd);
			}
			old_pwd = ft_strjoin("OLDPWD=", original);
			if (old_pwd != NULL)
			{
				data->envp[data->oldpwd_index] = ft_strdup(old_pwd);
				free(old_pwd);
			}
			free(pwd_value);
		}
	}
}

void	search_old_current(t_data *data)
{
	while (data->envp[data->pwd_index++] != NULL)
	{
		if (ft_strncmp(data->envp[data->pwd_index], "PWD=", 4) == 0)
			break ;
	}
	while (data->envp[data->oldpwd_index++] != NULL)
	{
		if (ft_strncmp(data->envp[data->oldpwd_index], "OLDPWD=", 7) == 0)
			break ;
	}
}

void	cd_without_arg(t_data *data, char *original)
{
	int	home;

	home = 0;
	while (data->envp[home++] != NULL)
	{
		if (ft_strncmp(data->envp[home], "HOME=", 5) == 0)
			break ;
	}
	if (chdir(data->envp[home] + 5) == 0)////if there is HOME
	{
		search_old_current(data);
		update_pwd(data, original);
	}
	else if (chdir(data->envp[home] + 5) != 0)//if HOME unset
		printf("bash: cd: HOME not set\n");
}

void	cd_with_one_arg(t_data *shell, char *original)
{
	if (chdir(shell->cmds->word_tok[1]) == 0)
	{
		search_old_current(shell);
		update_pwd(shell, original);
	}
	else if (chdir(shell->cmds->word_tok[1]) != 0)
		printf("bash: cd: %s No such file or directory\n", shell->cmds->word_tok[1]);
}

void	ft_cd(t_data *data, int number_of_inputs)
{
	char	*original;

	data->pwd_index = 0;
	data->oldpwd_index = 0;
	original = getcwd(data->pwd, sizeof(data->pwd));
	if (number_of_inputs <  2)// in case after cd there is no arguments -> goes to HOME	
		cd_without_arg(data, original);
	else if (number_of_inputs == 2)// goes to folder
		cd_with_one_arg(data, original);
	else if (number_of_inputs > 2)
		printf("bash: cd: too many arguments\n");
}
