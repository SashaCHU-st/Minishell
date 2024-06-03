/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:12:15 by aheinane          #+#    #+#             */
/*   Updated: 2024/06/03 10:50:19 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
//void init_msll(t_built *data, char **envp)
//{
//	data->env = NULL;
//}
int main (int argc, char **argv, char **envp)
{
	t_built data;
	int i = 2;
	int flag = 0;
	char wd[1000];
	char *env = envp[i];
	
	//init_msll(&data, envp);
	if(argc == 1)
		printf("");
	else if(argc > 1 &&  ft_strncmp(argv[1], "echo", 5) == 0) //if found echo, nujno esche $ pro env
	{
		if(argc > 2 && ft_strncmp(argv[2], "-n", 3) == 0)// in case there is -n as 3d arg
		{
			flag = 1;
			i = 3;
		}
		if(argc <=2)// in case after echo there is no arguments
			printf("there is nothing to print, put some arg"); 
		else
		{
			while(argc > i)
			{
				printf("%s", argv[i]);
				if(argc - 1 > i)
					printf(" ");
				i++;
			}
			if(!flag)
				printf("\n");
		}
	}
	else if (argc > 1 && ft_strncmp(argv[1], "pwd", 4) == 0)
    {
		printf("%s",getcwd(wd, sizeof(wd)));
    }
	else if (argc > 1 && ft_strncmp(argv[1], "cd", 3) == 0)//// DOES NOT REALLY WORKS!!!!!!!
    {
		if(argc <3)// in case after echo there is no arguments
			printf("");
		else if(argc == 3)
		{
			printf("%s\n",getcwd(wd, sizeof(wd)));
			if (chdir(argv[2]) != 0)
            {
                printf("ERROOR");
            }
			printf("%s",getcwd(wd, sizeof(wd)));
		}
    }
	else if(argc > 1 && ft_strncmp(argv[1], "env", 4) == 0)
	{
		int i =  0;
		while (env != NULL)
		{
			printf("%s\n", env);
			i++;
			env = envp[i];
		}
	}
	else if(argc > 1 && ft_strncmp(argv[1], "export", 7) == 0)
	{
		//char *env = envp[i];
		char *after_equal_sign;
		int i =  0;
		
		while (env != NULL && envp[i + 1] != NULL)/// envp[i + 1] dont pprint last line
		{
			after_equal_sign = ft_strchr(env, '=');
			printf("declare -x ");
			printf("%.*s", (int)(after_equal_sign - env), env);/// .* shows that the length of argument will be given as argument
			printf("=\"%s\"\n", after_equal_sign + 1);
			i++;
			env = envp[i];
		}	
		if(argc == 3)
		{
			char *added_var = ft_strjoin(argv[2], "");
			if (added_var != NULL)
			{
				envp[i] = added_var;
				envp[i + 1] = NULL; ///for ending list
				printf("declare -x %s\n", added_var);
			}
	}

	}
	else if(argc > 1 && ft_strncmp(argv[1], "unset", 6) == 0)
	{
		if(argc == 2)
		{
			printf("");
		}
		if(argc >= 3)
		{
			printf("Hello_world");
		}
	}
	//else
	//{
	//	printf("WRONGhello_world");
	//}
	return(0);
}