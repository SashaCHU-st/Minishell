/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:53:11 by epolkhov          #+#    #+#             */
/*   Updated: 2024/06/26 11:11:54 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
#include <fcntl.h>
# include "libft/libft.h"
#include "structs.h"
# include "builtins.h"

#define MAX_REDIRECTIONS 10

// typedef struct s_cmd
// {
// 	char	**word_tok;
// 	int		w_count;
	
// }	t_cmd;


// typedef struct s_data
// {
// 	t_cmd	*cmds;
// 	int		cmds_count;
// 	char	**pipe_tok;
// 	char	*hd_delimeter;
// 	int		hd_index;
// 	char	*tempfile_hd;
// }	t_data;

///////// input validation /////////
int     input_validation_redir(char *input);
int	    input_validation_pipes(char *input);
bool	check_space(char ch);
char	*change_to_space(char *line);
void	change_space_to_31(char *p_token);

bool	has_unclosed_quotes(char *line);
int	    skip_quotes(char *line, int i);
void	remove_quotes(char *str);
int     check_input_quotes_pipe(char *line);
void	error_message(char *msg);


char	**do_split(char const *s, char c);
void    *is_heredoc(char *line, t_data *tokens);
void	f_free_array(char **r);

void	put_one_space(char *line);
int	    skip_quotes(char *line, int i);



//////////////ADDED BY SASHA//////////////

#endif