/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 10:32:47 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/16 13:51:00 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef STRUCT_H
# define STRUCT_H

typedef enum {
	DEFAULT,
	HANDLER,
	HEREDOC,
	NO_SIGNALS
}	t_signal;

typedef enum {
	NONE,
	IN,
	OUT,
	HERE,
	APPEND
}	e_filetype;

typedef struct s_pipex{
	int		fd[2];
	int		fd_in;
	int		fd_out;
	char	**commands_path;
	char	**com_fir_child;
	char	**com_sec_child;
	int		second_child;
}	t_pipex;

typedef struct s_cmd
{
	char		**word_tok;
	int			w_count;
	char		**filenames;
	int			*filetype;
	int			number_of_redir;
	e_filetype	type;
}	t_cmd;

typedef struct s_data
{
	t_cmd	*cmds;
	int		cmds_count;
	char	**pipe_tok;
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
	int		parent_out;
	int		parent_in;
	int		*pid;
	int		exit_status;
	int		hd_interrupt;
	char	*path;
	int		var_name_len;
	int		envp_size;
	int		hd_index;
}	t_data;

#endif