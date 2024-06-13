/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:53:11 by epolkhov          #+#    #+#             */
/*   Updated: 2024/06/06 21:33:01 by epolkhov         ###   ########.fr       */
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

typedef struct s_tok
{
	int		size;
	char	**pipe_tok;
	char	*hd_delimeter;
	int		hd_index;
	char	*tempfile_hd;
}	t_tok;

typedef struct Tokens
{
	t_tok	*p_tokens;
	
}	Tokens;

///////// input validation /////////
void	input_validation_redir(char *input);
void	input_validation_pipes(char *input);
bool	check_space(char ch);
bool	has_unclosed_quotes(char *line);
void	error_message(char *msg);

char	**do_split(char const *s, char c);
void	*is_heredoc(char *line);
void	f_free_array(char **r);

#endif