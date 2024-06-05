/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:32:50 by aheinane          #+#    #+#             */
/*   Updated: 2024/06/05 13:18:11 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
#define BUILTINS_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_built{
	char **env;
} t_built;

int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	ft_words(const char *str, char c);
char	*ft_wd(const char *str, char c);
void	free_w(size_t i, char **ptr);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
char *ft_strpbrk(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str );
void deleteEnvVar(char **envp, const char *arg);
void ft_echo(int argc, char **argv);
void ft_export(char *env, char **envp, int argc, char **argv);
void ft_env(char *env, char **envp);
void ft_unset(int argc, char **envp, char **argv);
void ft_cd(int argc, char **argv);
#endif