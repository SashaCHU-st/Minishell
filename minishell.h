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
# include <fcntl.h>
# include "libft/libft.h"
# include "builtins.h"
# include "structs.h"


///////// input validation /////////
int		input_validation_redir(char *input);
int		input_validation_pipes(char *input);
bool	check_space(char ch);
char	*change_to_space(char *line);
void	change_space_to_31(char *p_token);

bool	has_unclosed_quotes(char *line);
int		skip_quotes(char *line, int i);
void	remove_quotes(char *str);
int		check_input_quotes_pipe(char *line);
void	error_message(char *msg);


char	**do_split(char const *s, char c);
void	*is_heredoc(char *line, t_data *tokens);
void	f_free_array(char **r);
void	f_free_array_3(char ***str);
void	put_one_space(char *line);
int	skip_quotes(char *line, int i);

void	put_one_space(char *line);
int		skip_quotes(char *line, int i);
int		is_in_quotes(char c, int *in_single_quote, int *in_double_quote);
char	*hd_filename(int count);
char	*expand_var(t_data *shell, char *line);
void	make_redirs(t_data *tokens);
void	remove_redir_from_input(t_data *tokens);

char	*ft_strncpy(char *dest, const char *src, size_t n);
char	*ft_strndup(const char *str, size_t n);

//////////////ADDED BY SASHA//////////////

#endif