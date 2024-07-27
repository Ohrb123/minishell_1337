/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:56:03 by oelharbi          #+#    #+#             */
/*   Updated: 2024/05/22 15:26:20 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	s;

	s = (long)n;
	if (s < 0)
	{
		ft_putchar_fd('-', fd);
		s *= -1;
	}
	if (s / 10)
		ft_putnbr_fd((s / 10), fd);
	ft_putchar_fd((s % 10) + 48, fd);
}
