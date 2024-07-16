/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:53:11 by epolkhov          #+#    #+#             */
/*   Updated: 2024/07/15 16:03:26 by aheinane         ###   ########.fr       */
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
# include <errno.h>


extern int signal_status;
///////// input validation /////////

int		input_validation_redir(t_data *shell, char *input);
int		input_validation_pipes(t_data *shell, char *input);

bool	check_space(char ch);
char	*change_to_space(char *line);
void	change_space_to_31(char *p_token);

bool	has_unclosed_quotes(char *line);
int		skip_quotes(char *line, int i);
void	remove_quotes(char *str);
int		skip_quotes(char *line, int i);
int		check_input_quotes_pipe(t_data *shell, char *line);
int		is_in_quotes(char c, int *in_single_quote, int *in_double_quote);
void	error_message(t_data *shell, char *msg, int status);

void	init_t_data(t_data *data);
void	init_cmd(t_cmd *cmd);

////////////// parsing ///////////////

char	**do_split(char const *s, char c);
void	split_line(char *line, t_data *shell);
void	*is_heredoc(char *line, t_data *tokens);
char	*hd_filename(t_data *shell, int count);
char	*expand_var(t_data *shell, char *line);
void	make_redirs(t_data *tokens);
void	remove_redir_from_input(t_data *tokens);

//////// utils functions /////////////////

char	*ft_strncpy(char *dest, const char *src, size_t n);
char	*ft_strndup(const char *str, size_t n);
int		ft_strcmp(char *s1, char *s2);

//////////////exit and free//////////////

void    get_signal(t_data *shell, t_signal mode);

void	exit_free(t_data *shell, int status);
void	free_all(t_data *shell);
void	f_free_cmds(t_cmd *cmds, int cmds_count);
void	free_t_data(t_data *shell);
void	ft_exit(t_data *shell, char **args);
void	f_free_array(char **r);

//static char	*get_expand(t_data *shell, char *line);
//static int	end_character(char c);
# endif