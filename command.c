/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:43:44 by aheinane          #+#    #+#             */
/*   Updated: 2024/06/19 14:02:54 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

void	ft_pwd(void)
{
	printf("%s\n", getcwd(NULL, 0));
}

void	if_quotes(char *str)
{
	char	*write_ptr;
	char	quote_char;
	char	*read_ptr;

	write_ptr = str;
	read_ptr = str;
	quote_char = 0;
	while (*read_ptr)
	{
		if (*read_ptr == '\'' || *read_ptr == '\"')
		{
			if (quote_char == 0)
				quote_char = *read_ptr;
			else if (quote_char == *read_ptr)
				quote_char = 0;
			read_ptr++;
		}
		else
			*write_ptr++ = *read_ptr++;
	}
	*write_ptr = '\0';
}

void	ft_unset(t_built *data, int number_of_inputs)
{
	int	k;

	k = 1;
	if (number_of_inputs == 1)
		printf(" ");
	if (number_of_inputs >= 2)
	{
		while (k < number_of_inputs)
			unset_var(data, data->inputs[k++]);
	}
}

void	ft_echo(t_built *data, int number_of_inputs)
{
	int	flag;
	int	i;

	i = 2;
	flag = 0;
	if (number_of_inputs > 2 && ft_strncmp(data->inputs[1], "-n", 3) == 0)// in case there is -n as 3d arg
	{
		flag = 1;
		i = 3;
	}
	if (number_of_inputs <= 1)// in case after echo there is no arguments
		printf("there is nothing to print, put some arg");
	else
	{
		while (number_of_inputs >= i)
		{
			printf("%s", data->inputs[i - 1]);
			if (number_of_inputs - 1 > i)
				printf(" ");
			i++;
		}
		if (!flag)
			printf("\n");
	}
}

void	ft_env(t_built *data)
{	
	int		i;
	char	*kuku;

	i = 0;
	while (data->envp[i] != NULL)
	{
		kuku = ft_strchr(data->envp[i], '=');
		if (kuku != NULL)
		{
			printf("%s\n", data->envp[i]);
			i++;
		}
		else
			i++;
	}
}
