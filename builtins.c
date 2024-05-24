/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:12:15 by aheinane          #+#    #+#             */
/*   Updated: 2024/05/24 13:26:11 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] > s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		else if (s1[i] < s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
int main (int argc, char **argv, char **envp)
{
	int i = 2;
	int flag = 0;
	char wd[1000];
	
	if(argc > 1 &&  ft_strncmp(argv[1], "echo", 4) == 0) //if found echo, nujno esche $ pro env
	{
		if(argc > 2 && ft_strncmp(argv[2], "-n", 2) == 0)// in case there is -n as 3d arg
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
	else if (ft_strncmp(argv[1], "pwd", 3) == 0)
    {
		printf("%s",getcwd(wd, sizeof(wd)));
    }
	else if (ft_strncmp(argv[1], "cd", 3) == 0)//// DOES NOT REALLY WORKS!!!!!!!
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
	else if(ft_strncmp(argv[1], "env", 4) == 0)
	{
		int i =  0;
		char *env = envp[i];
		while (env != NULL)
		{
			printf("%s\n", env);
			i++;
			env = envp[i];
		}
	}
	else if(ft_strncmp(argv[1], "export", 7) == 0)
	{
		int i =  0;
		char *env = envp[i];
		while (env != NULL)
		{
			printf("%s\n", env);
			i++;
			env = envp[i];
		}
	}
	else
	{
		printf("WRONGhello_world");
	}
	return(0);
}