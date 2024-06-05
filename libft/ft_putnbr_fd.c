/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:15:08 by aheinane          #+#    #+#             */
/*   Updated: 2023/11/13 15:16:04 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	i;

	i = n;
	if (i < 0)
	{
		ft_putchar_fd ('-', fd);
		i = -i;
	}
	if (i >= 10)
	{
		ft_putnbr_fd (i / 10, fd);
		ft_putnbr_fd (i % 10, fd);
	}
	else
	{
		ft_putchar_fd(i + '0', fd);
	}
}
