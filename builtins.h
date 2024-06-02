/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:32:50 by aheinane          #+#    #+#             */
/*   Updated: 2024/05/31 16:02:15 by aheinane         ###   ########.fr       */
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
char *ft_strpbrk( char *s1, char *s2);

#endif