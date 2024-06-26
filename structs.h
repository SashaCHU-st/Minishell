/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 10:32:47 by aheinane          #+#    #+#             */
/*   Updated: 2024/06/26 10:32:50 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
#define STRUCT_H

typedef struct s_cmd
{
	char	**word_tok;
	int		w_count;
	
}	t_cmd;

typedef struct s_data
{
	t_cmd	*cmds;
	int		cmds_count;
	char	**pipe_tok;
	char	*hd_delimeter;
	int		hd_index;
	char	*tempfile_hd;
}	t_data;

typedef struct s_built{
	char **envp;
	char **new_envp;
	int argc;
	char **argv;
	char pwd[1000];
	int pwd_index;
	int oldpwd_index;
	char *input_copy;
	//int number_of_inputs;
	//int envp_size;
	//char **input;
	t_data data;

} t_built;

#endif