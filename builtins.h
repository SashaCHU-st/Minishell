/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:32:50 by aheinane          #+#    #+#             */
/*   Updated: 2024/06/19 13:55:37 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
#define BUILTINS_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "structs.h"
#include "minishell.h"

// typedef struct s_built{
// 	char **envp;
// 	char **new_envp;
// 	int argc;
// 	char **argv;
// 	char pwd[1000];
// 	int pwd_index;
// 	int oldpwd_index;
// 	char *input_copy;
// 	//int number_of_inputs;
// 	//int envp_size;
// 	//char **inputs;
// 	t_data data;

// } t_built;

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

#endif