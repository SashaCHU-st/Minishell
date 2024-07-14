/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:39:27 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/14 18:30:23 by aheinane         ###   ########.fr       */
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

void	checking_home(int found_home, t_data *data, int home, char *original)
{
	if (found_home)
	{
		if (chdir(data->envp[home] + 5) == 0)
		{
			search_old_current(data);
			update_pwd(data, original);
		}
		else
			ft_putstr_fd("bash: cd: HOME not set\n", 1);
	}
	else
		ft_putstr_fd("bash: cd: HOME not set\n", 1);
}
