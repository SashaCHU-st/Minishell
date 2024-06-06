/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:12:15 by aheinane          #+#    #+#             */
/*   Updated: 2024/06/06 08:50:05 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int main (int argc, char **argv, char **envp)
{
	t_built data;
	data.envp = envp;
	
	if(argc == 1)
		printf("");
	else if(argc > 1 &&  ft_strncmp(argv[1], "echo", 5) == 0) //if found echo, nujno esche $ pro env
		ft_echo(argc, argv);
	else if (argc > 1 && ft_strncmp(argv[1], "pwd", 4) == 0)
		ft_pwd(envp);
	else if (argc > 1 && ft_strncmp(argv[1], "cd", 3) == 0)//// DOES NOT REALLY WORKS!!!!!!!
		ft_cd(&data, argc, argv);
	else if(argc > 1 && ft_strncmp(argv[1], "env", 4) == 0)
		ft_env(&data);
	else if(argc > 1 && ft_strncmp(argv[1], "export", 7) == 0)
		ft_export(&data, argc,argv);
	else if(argc > 1 && ft_strncmp(argv[1], "unset", 6) == 0)
		ft_unset(&data, argc,argv);
	return(0);
}