/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:53:11 by epolkhov          #+#    #+#             */
/*   Updated: 2024/07/04 16:48:01 by aheinane         ###   ########.fr       */
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
# include <termios.h>
# include <signal.h>


///////// input validation /////////
int		input_validation_redir(t_data *shell, char *input);
int		input_validation_pipes(t_data *shell, char *input);
bool	check_space(char ch);
char	*change_to_space(char *line);
void	change_space_to_31(char *p_token);

bool	has_unclosed_quotes(char *line);
int		skip_quotes(char *line, int i);
void	remove_quotes(char *str);
int		check_input_quotes_pipe(t_data *shell, char *line);
void	error_message(t_data *shell, char *msg, int status);


char	**do_split(char const *s, char c);
void	*is_heredoc(char *line, t_data *tokens);
void	f_free_array(char **r);
//void	f_free_array_3(char ***str);
//void	put_one_space(char *line);
int		skip_quotes(char *line, int i);

//void	put_one_space(char *line);
int		skip_quotes(char *line, int i);
int		is_in_quotes(char c, int *in_single_quote, int *in_double_quote);
char	*hd_filename(t_data *shell, int count);
char	*expand_var(t_data *shell, char *line);
void	make_redirs(t_data *tokens);
void	remove_redir_from_input(t_data *tokens);

char	*ft_strncpy(char *dest, const char *src, size_t n);
char	*ft_strndup(const char *str, size_t n);
int		ft_strcmp(char *s1, char *s2);

//////////////ADDED BY SASHA//////////////

void	split_line(char *line, t_data *shell);
t_cmd	split_into_wtok(char *pipe_token, t_cmd cmd);
void 	init_t_data(t_data *data);
void    get_signal(t_signal mode);
void	exit_free(t_data *shell, int status);
void	free_all(t_data *shell);
void	f_free_cmds(t_cmd *cmds, int cmds_count);
void	ft_exit(t_data *shell, char **args);


#endif