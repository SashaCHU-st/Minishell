/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:32:50 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/02 15:03:22 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
#define BUILTINS_H
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>
#include "minishell.h"
#include "structs.h"


typedef struct s_pipex{
	int		fd[2];
	int		fd_in;
	int		fd_out;
	char	**commands_path;
	char	**com_fir_child;
	char	**com_sec_child;
	int second_child;
	
} t_pipex;

int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_words(const char *str, char c);
char	*ft_wd(const char *str, char c);
void	free_w(size_t i, char **ptr);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strpbrk(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str );
char	*ft_strdup(const char *src);
void	unset_var(t_built *data, char *arg);
void	ft_echo(t_built *data, int number_of_inputs);
void	ft_export(t_built *data, int number_of_inputs);
void	ft_env(t_built *data);
void	ft_unset(t_built *data, int number_of_inputs);
void	ft_cd(t_built *data, int number_of_inputs);
void	ft_pwd(void);
int		is_var_in_envp(char *arg, t_built *data);
void	if_quotes(char *str);
void	cd_without_arg(t_built *data, char *original);
void	cd_with_one_arg(t_built *data, char *original);
void	update_pwd(t_built *data, char *original);
void	search_old_current(t_built *data);
void	checking_export (t_built *data);
void	not_in_var(t_built *data, char *input_copy, char *added_var);
void	export_with(t_built *data, int number_of_inputs);
void	if_error_input(char *input_copy);


//////
char	*mine_path(t_built *data);
void	creating_children(t_pipex *pipex, t_built *data, int num_commands);
void	free_fun(t_pipex *pipex);
int		open_fd_in(t_pipex *pipex, t_built *data);
void	open_fd_out(t_pipex *pipex, t_built *data, int number_of_inputs);
void	free_array(char **array);
void	ft_error(void);
char	*path_for_commands(t_pipex *pipex, char **child_command);

void	check_permissions(t_built *data);
int		if_builtins(t_built *data, t_cmd *cmd);
void	close_and_wait(t_built *shell, t_pipex *pipex, int first_child);
//void	close_and_wait(t_pipex *data, int first_child, int second_child);
void	fun_second_child(t_built *shell, t_pipex pipex);
void	fun_first_child(t_built *shell, t_pipex pipex);

#endif