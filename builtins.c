/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:12:15 by aheinane          #+#    #+#             */
/*   Updated: 2024/05/21 13:12:22 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
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
int main (int argc, char **argv)
{
	int i = 2;
	int flag = 0;
	if(ft_strncmp(argv[2], "-n", 2) == 0)// in case there is -n as 3d arg
	{
		flag = 1;
		i = 3;
	}
	if(ft_strncmp(argv[1], "echo", 4) == 0) //if found echo
	{
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
	else
	{
		printf("WRONGhello_world");
	}
	return(0);
}