/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 10:32:47 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/04 16:15:49 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
#define STRUCT_H

// typedef enum {
//     NONE,
//     IN,
//     OUT,
//     HERE,
//     APPEND
// } e_filetype;

// typedef struct s_cmd
// {
// 	char	**word_tok;
// 	int		w_count;

// 	char **filenames;
// 	int *filetype;
// 	int number_of_redir;
// 	// int	redir_count;
// 	 e_filetype	type;
// 	//int flag_amb_redir;
	
// }	t_cmd;

// typedef struct s_data
// {
// 	t_cmd	*cmds;
// 	int		cmds_count;
// 	char	**pipe_tok;
// 	char	*hd_delimeter;
// 	int		hd_count;
// 	char	*tempfile_hd;
// 	// t_build * shell;
// }	t_data;

// typedef struct s_built{
// 	char **envp;
// 	char **new_envp;
// 	char pwd[1000];
// 	int pwd_index;
// 	int oldpwd_index;
// 	char *input_copy;
// 	t_data data;

// } t_built;
typedef enum {
    NONE,
    IN,
    OUT,
    HERE,
    APPEND
} e_filetype;

typedef struct s_cmd
{
	char	**word_tok;
	int		w_count;

	char **filenames;
	int *filetype;
	int number_of_redir;
	// int	redir_count;
	 e_filetype	type;
	//int flag_amb_redir;
	
}	t_cmd;

typedef struct s_built t_built;

typedef struct s_data
{
	t_cmd	*cmds;
	int		cmds_count;
	char	**pipe_tok;
	char	*hd_delimeter;
	int		hd_count;
	char	*tempfile_hd;
	char **envp;
	char **new_envp;
	char pwd[1000];
	int pwd_index;
	int oldpwd_index;
	char *input_copy;
	// t_build * shell;
}	t_data;


#endif