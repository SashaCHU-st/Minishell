/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 10:32:47 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/11 19:55:05 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
#define STRUCT_H

typedef enum {
    DEFAULT,
    HANDLER,
    HEREDOC,
    //NO_SIGNALS
} t_signal;

typedef enum {
    NONE,
    IN,
    OUT,
    HERE,
    APPEND
} e_filetype;

typedef struct s_pipex{
	int		fd[2];
	int		fd_in;
	int		fd_out;
	char	**commands_path;
	char	**com_fir_child;
	char	**com_sec_child;
	int second_child;
	    int stdin_backup;
    int stdout_backup;
	
} t_pipex;
typedef struct s_cmd
{
	char	**word_tok; // word_tok[0] = cat; word_tok[1] = wc 
	int		w_count; // skolko slov commande


	char **filenames;// reditrect names
	int *filetype; // tip file
	int number_of_redir;

	// int	redir_count;
	e_filetype	type;
	//int flag_amb_redir;
	
}	t_cmd;

typedef struct s_built t_built;

typedef struct s_data
{
	t_cmd	*cmds;
	int		cmds_count; /// skilko command eli et pipe
	char	**pipe_tok;// vsya commanda <1.txt cat | wc >3.txt; pipe_tok[0] = 1.txt cat  ; pipe_tok = wc 3.txt
	char	*hd_delimeter;
	int		hd_count;
	char	*tempfile_hd;
	char	**envp;
	char	**new_envp;
	char	pwd[1000];
	int		pwd_index;
	int		oldpwd_index;
	char	*input_copy;
	int		redir_count;
	int		pipe_count;
	int		**pipe;
	int parent_out;
	int *pid;
	int	exit_status;
	
	// t_build * shell;
}	t_data;




#endif